#ifndef AT_CLIENT_ATCLIENT_H
#define AT_CLIENT_ATCLIENT_H

#include <vector>

#include "Utils.h"
#include "Server.h"
#include "AtSign.h"

class AtClient {
private:
    AtClient() {}

public:

    static Server lookupSecondaryForAtSign(Server &rootServer, const AtSign &atSign);

    static std::vector<std::string> scan(Server &secondaryServer);

    static std::string lookup(Server &secondaryServer, const std::string &property);

    static std::string llookup(Server &secondaryServer, const std::string &property);

    static std::string plookup(Server &secondaryServer, const std::string &property);

    static std::string from(Server &secondaryServer, const AtSign &atSign);

    static std::string pkam(Server &secondaryServer, const std::string &signature);
};

#endif //AT_CLIENT_ATCLIENT_H
