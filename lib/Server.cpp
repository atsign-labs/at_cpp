#include <iostream>

#include "Server.h"
#include "lib/Command.h"

Utils::UniquePtr<SSL_CTX> Server::ctx;

Server::Server(const std::string &host, const std::string &port)
        : host(host), port(port), connected(false) {

    if (ctx == nullptr) {
#if OPENSSL_VERSION_NUMBER < 0x10100000L
        SSL_library_init();
        SSL_load_error_strings();
#endif

        /* Set up the SSL context */

#if OPENSSL_VERSION_NUMBER < 0x10100000L
        auto ctx = Utils::UniquePtr<SSL_CTX>(SSL_CTX_new(SSLv23_client_method()));
#else
        ctx = Utils::UniquePtr<SSL_CTX>(SSL_CTX_new(TLS_client_method()));
#endif
        if (SSL_CTX_set_default_verify_paths(ctx.get()) != 1) {
            print_errors_and_exit("Error setting up trust store");
        }
    }
}

void Server::connect() {
    std::string host_port = host + ":" + port;
    auto bio = Utils::UniquePtr<BIO>(BIO_new_connect(host_port.c_str()));

    if (bio == nullptr) {
        print_errors_and_exit("Error in BIO_new_connect");
    }

    if (BIO_do_connect(bio.get()) <= 0) {
        print_errors_and_exit("Error in BIO_do_connect");
    }

    ssl_bio = move(bio) | Utils::UniquePtr<BIO>(BIO_new_ssl(ctx.get(), 1));
    SSL_set_tlsext_host_name(get_ssl(ssl_bio.get()), host.c_str());

#if OPENSSL_VERSION_NUMBER >= 0x10100000L
    SSL_set1_host(get_ssl(ssl_bio.get()), host.c_str());
#endif

    if (BIO_do_handshake(ssl_bio.get()) <= 0) {
        print_errors_and_exit("Error in BIO_do_handshake");
    }

    // TODO: need to verify server certificate
    // Utils::verify_the_certificate(Utils::get_ssl(ssl_bio.get()), host.c_str());

    connected = true;
}

std::string Server::executeCommand(const Command &command,
                                   const std::string &requestEol,
                                   const char *responseEol) {
    if (!connected) {
        this->connect();
    }

    BIO *bio = ssl_bio.get();
    send_raw_request(bio, command.getValue(), requestEol);
    return receive_raw_message(bio, responseEol);
}

[[noreturn]] void Server::print_errors_and_exit(const char *message) {
    fprintf(stderr, "%s\n", message);
    ERR_print_errors_fp(stderr);
    exit(1);
}

[[noreturn]] void Server::print_errors_and_throw(const char *message) {
    Utils::StringBIO bio;
    ERR_print_errors(bio.bio());
    throw std::runtime_error(std::string(message) + "\n" + std::move(bio).str());
}

std::string Server::receive_some_data(BIO *bio) {
    char buffer[1024];
    int len = BIO_read(bio, buffer, sizeof(buffer));
    if (len < 0) {
        print_errors_and_throw("error in BIO_read");
    } else if (len > 0) {
        return std::string(buffer, len);
    } else if (BIO_should_retry(bio)) {
        return receive_some_data(bio);
    } else {
        print_errors_and_throw("empty BIO_read");
    }
}

std::string Server::receive_raw_message(BIO *bio, const char *eol) {
    std::string data = receive_some_data(bio);
    char *endOfData = strstr(&data[0], eol);
    while (endOfData == nullptr) {
        data += receive_some_data(bio);
        endOfData = strstr(&data[0], eol);
    }

    int pos = data[0] == '@' ? 1 : 0;

    return data.substr(pos, data.size() - strlen(endOfData) - pos);
}

void Server::send_raw_request(BIO *bio, const std::string &line, const std::string &eol) {
    std::string request = line + eol;
    std::cout << "SEND: [" << request << "]" << std::endl;
    BIO_write(bio, request.data(), request.size());
    BIO_flush(bio);
}

SSL *Server::get_ssl(BIO *bio) {
    SSL *ssl = nullptr;
    BIO_get_ssl(bio, &ssl);
    if (ssl == nullptr) {
        print_errors_and_exit("Error in BIO_get_ssl");
    }
    return ssl;
}

void Server::verify_the_certificate(SSL *ssl, const std::string &expected_hostname) {
    int err = SSL_get_verify_result(ssl);
    if (err != X509_V_OK) {
        const char *message = X509_verify_cert_error_string(err);
        fprintf(stderr, "Certificate verification error: %s (%d)\n", message, err);
        exit(1);
    }
    X509 *cert = SSL_get_peer_certificate(ssl);
    if (cert == nullptr) {
        fprintf(stderr, "No certificate was presented by the server\n");
        exit(1);
    }
#if OPENSSL_VERSION_NUMBER < 0x10100000L
    if (X509_check_host(cert, expected_hostname.data(), expected_hostname.size(), 0, nullptr) != 1) {
        fprintf(stderr, "Certificate verification error: X509_check_host\n");
        exit(1);
    }
#else
    // X509_check_host is called automatically during verification,
    // because we set it up in main().
    (void) expected_hostname;
#endif
}

