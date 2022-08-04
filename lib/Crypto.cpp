#include <memory>
#include <iostream>
#include "Crypto.h"

std::vector<unsigned char> Crypto::GenerateRsaSignByFile(const std::string &message,
                                                         const std::string &pri_filename) {
    OpenSSL_add_all_algorithms();
    BIO *in = BIO_new(BIO_s_file());
    if (in == nullptr) {
        std::cout << "BIO_new failed" << std::endl;
        return std::vector<unsigned char>();
    }
    BIO_read_filename(in, pri_filename.c_str());
    RSA *rsa = PEM_read_bio_RSAPrivateKey(in, nullptr, nullptr, nullptr);
    BIO_free(in);

    if (rsa == nullptr) {
        std::cout << "PEM_read_bio_RSAPrivateKey failed" << std::endl;
        return std::vector<unsigned char>();
    }
    unsigned int size = RSA_size(rsa);
    std::vector<unsigned char> sign;
    sign.resize(size);

    // Buffer to hold the calculated digest
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, message.c_str(), message.length());
    SHA256_Final(digest, &ctx);

    int ret =
            RSA_sign(NID_sha256, (const unsigned char *) digest,
                     SHA256_DIGEST_LENGTH, (unsigned char *) sign.data(), &size, rsa);
    RSA_free(rsa);
    if (ret != 1) {
        std::cout << "RSA_sign failed" << std::endl;
        return std::vector<unsigned char>();
    }
    return sign;
}

std::string Crypto::Base64Encode(const std::vector<unsigned char> &binary) {
    std::unique_ptr<BIO, BIOFreeAll> b64(BIO_new(BIO_f_base64()));
    BIO_set_flags(b64.get(), BIO_FLAGS_BASE64_NO_NL);
    BIO *sink = BIO_new(BIO_s_mem());
    BIO_push(b64.get(), sink);
    BIO_write(b64.get(), binary.data(), binary.size());
    BIO_flush(b64.get());
    const char *encoded;
    const long len = BIO_get_mem_data(sink, &encoded);
    return std::string(encoded, len);
}
