#ifndef AT_CLIENT_CPP_DEMO_LLOOKUPCOMMAND_H
#define AT_CLIENT_CPP_DEMO_LLOOKUPCOMMAND_H

#include "lib/Command.h"

class LlookupCommand : public Command {
public:

    LlookupCommand(const std::string &property) : Command("llookup"), property(property) {}

    virtual std::string getValue() const {
        return verb + ":" + property;
    }

private:

    std::string property;

};


#endif //AT_CLIENT_CPP_DEMO_LLOOKUPCOMMAND_H
