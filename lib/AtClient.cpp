#include "cmake-build-debug/_deps/json-src/single_include/nlohmann/json.hpp"

#include "Utils.h"
#include "Server.h"
#include "AtClient.h"
#include "LookUpSecondaryForAtSignCommand.h"
#include "ScanCommand.h"
#include "LlookupCommand.h"
#include "LookupCommand.h"
#include "PlookupCommand.h"
#include "FromCommand.h"
#include "PkamCommand.h"


Server AtClient::lookupSecondaryForAtSign(Server &rootServer, const AtSign &atSign) {
    std::string response = rootServer.executeCommand(LookUpSecondaryForAtSignCommand(atSign));
    printf("received response : %s\n", response.c_str());
    std::vector<std::string> tokens = Utils::parseResponse(response);
    return {tokens[0], tokens[1]};
}

std::vector<std::string> AtClient::scan(Server &secondaryServer) {
    std::string response = secondaryServer.executeCommand(ScanCommand(), "\r\n", "\n@");
    printf("received response : %s\n", response.c_str());
    nlohmann::json json_response = nlohmann::json::parse(response.substr(strlen("data:"), response.size()));
    return json_response.get<std::vector<std::string>>();
}

std::string AtClient::lookup(Server &secondaryServer, const std::string &property) {
    std::string response = secondaryServer.executeCommand(LookupCommand(property), "\r\n", "\n");
    printf("received response : %s\n", response.c_str());
    std::vector<std::string> tokens = Utils::parseResponse(response);
    return tokens[1];
}

std::string AtClient::llookup(Server &secondaryServer, const std::string &property) {
    std::string response = secondaryServer.executeCommand(LlookupCommand(property), "\r\n", "\n");
    printf("received response : %s\n", response.c_str());
    std::vector<std::string> tokens = Utils::parseResponse(response);
    return tokens[1];
}

std::string AtClient::plookup(Server &secondaryServer, const std::string &property) {
    std::string response = secondaryServer.executeCommand(PlookupCommand(property), "\r\n", "\n");
    printf("received response : %s\n", response.c_str());

    std::vector<std::string> tokens = Utils::parseResponse(response);
    return tokens[1];
}

std::string AtClient::from(Server &secondaryServer, const AtSign &atSign) {
    std::string response = secondaryServer.executeCommand(FromCommand(atSign), "\n", "\n");
    printf("received response : %s\n", response.c_str());
    return response.substr(strlen("data:"), response.size());
}

std::string AtClient::pkam(Server &secondaryServer, const std::string &signature) {
    std::string response = secondaryServer.executeCommand(PkamCommand(signature), "\n", "\n");
    printf("received response : %s\n", response.c_str());
    return response;
}
