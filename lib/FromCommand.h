#ifndef AT_CLIENT_CPP_DEMO_FROMCOMMAND_H
#define AT_CLIENT_CPP_DEMO_FROMCOMMAND_H

#include <string>
#include "lib/Command.h"

class FromCommand : public Command {

public:
    FromCommand(const AtSign &atSign) : Command("from"), atSign(atSign) {}

    virtual std::string getValue() const {
        return verb + ":@" + atSign.getValue();
    }

private:
    AtSign atSign;
};


#endif //AT_CLIENT_CPP_DEMO_FROMCOMMAND_H
