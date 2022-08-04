#ifndef AT_CLIENT_SERVER_H
#define AT_CLIENT_SERVER_H

#include "Utils.h"
#include "lib/Command.h"

class Server {
public:
    Server(const std::string &host, const std::string &port);

    void connect();

    std::string executeCommand(const Command &command,
                               const std::string &requestEol = "\r\n",
                               const char *responseEol = "\r\n");

private:
    [[noreturn]] static void print_errors_and_exit(const char *message);

    [[noreturn]] static void print_errors_and_throw(const char *message);

    std::string receive_some_data(BIO *bio);

    std::string receive_raw_message(BIO *bio, const char *eol = "\r\n");

    static void send_raw_request(BIO *bio, const std::string &line, const std::string &eol = "\r\n");

    static SSL *get_ssl(BIO *bio);

    static void verify_the_certificate(SSL *ssl, const std::string &expected_hostname);

    std::string host;

    std::string port;

    bool connected;

    Utils::UniquePtr<BIO> ssl_bio;

    static Utils::UniquePtr<SSL_CTX> ctx;
};

#endif //AT_CLIENT_SERVER_H
