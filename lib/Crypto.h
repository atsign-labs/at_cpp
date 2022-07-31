#ifndef AT_CLIENT_CRYPTO_H
#define AT_CLIENT_CRYPTO_H

#include <vector>
#include <openssl/ssl.h>

class Crypto {
public:
    static std::vector<unsigned char> GenerateRsaSignByFile(const std::string &message,
                                                            const std::string &pri_filename);

    static std::string Base64Encode(const std::vector<unsigned char> &binary);

private:
    struct BIOFreeAll {
        void operator()(BIO *p) { BIO_free_all(p); }
    };
};

#endif //AT_CLIENT_CRYPTO_H
