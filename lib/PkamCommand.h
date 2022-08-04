#ifndef AT_CLIENT_CPP_DEMO_PKAMCOMMAND_H
#define AT_CLIENT_CPP_DEMO_PKAMCOMMAND_H

#include "lib/Command.h"

class PkamCommand : public Command {
public:

    PkamCommand(const std::string &signature) : Command("pkam"), signature(signature) {}

    virtual std::string getValue() const {
        return verb + ":" + signature;
    }

private:

    std::string signature;

};


#endif //AT_CLIENT_CPP_DEMO_PKAMCOMMAND_H
