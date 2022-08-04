#ifndef AT_CLIENT_CPP_DEMO_SCANCOMMAND_H
#define AT_CLIENT_CPP_DEMO_SCANCOMMAND_H

#include "lib/Command.h"

class ScanCommand : public Command {
public:
    ScanCommand(): Command(){}
    virtual std::string getValue() const{
        return "scan";
    }
};


#endif //AT_CLIENT_CPP_DEMO_SCANCOMMAND_H
