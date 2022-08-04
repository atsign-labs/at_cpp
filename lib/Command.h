#ifndef AT_CLIENT_CPP_DEMO_COMMAND_H
#define AT_CLIENT_CPP_DEMO_COMMAND_H

#include <string>

class Command {

public:
    Command(const std::string &verb = "") : verb(verb) {}

    virtual std::string getValue() const = 0;

protected:
    std::string verb;
};


#endif //AT_CLIENT_CPP_DEMO_COMMAND_H
