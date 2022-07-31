#ifndef AT_CLIENT_CPP_DEMO_PLOOKUPCOMMAND_H
#define AT_CLIENT_CPP_DEMO_PLOOKUPCOMMAND_H

#include "lib/Command.h"

class PlookupCommand : public Command {
public:

    PlookupCommand(const std::string &property) : Command("plookup"), property(property) {}

    virtual std::string getValue() const {
        return verb + ":" + property;
    }

private:

    std::string property;

};


#endif //AT_CLIENT_CPP_DEMO_PLOOKUPCOMMAND_H
