#ifndef AT_CLIENT_CPP_DEMO_LOOKUPCOMMAND_H
#define AT_CLIENT_CPP_DEMO_LOOKUPCOMMAND_H

#include "lib/Command.h"

class LookupCommand : public Command {
public:

    LookupCommand(const std::string &property) : Command("lookup"), property(property) {}

    virtual std::string getValue() const {
        return verb + ":" + property;
    }

private:

    std::string property;

};


#endif //AT_CLIENT_CPP_DEMO_LOOKUPCOMMAND_H
