#ifndef AT_CLIENT_CPP_DEMO_LOOKUPSECONDARYFORATSIGNCOMMAND_H
#define AT_CLIENT_CPP_DEMO_LOOKUPSECONDARYFORATSIGNCOMMAND_H

#include <string>
#include "lib/Command.h"

class LookUpSecondaryForAtSignCommand : public Command {

public:
    LookUpSecondaryForAtSignCommand(const AtSign &atSign) : Command(), atSign(atSign) {}

    virtual std::string getValue() const {
        return atSign.getValue();
    }

private:
    AtSign atSign;
};


#endif //AT_CLIENT_CPP_DEMO_LOOKUPSECONDARYFORATSIGNCOMMAND_H
