#ifndef AT_CLIENT_CPP_DEMO_ATSIGN_H
#define AT_CLIENT_CPP_DEMO_ATSIGN_H

#include <string>

class AtSign {

public:
    AtSign(const std::string &atSign) : atSign(atSign) {}

    std::string getValue() const {
        if (atSign[0] == '@') {
            return atSign.substr(1, atSign.length() - 1);
        }

        return atSign;
    }

private:
    std::string atSign;
};

#endif //AT_CLIENT_CPP_DEMO_ATSIGN_H
