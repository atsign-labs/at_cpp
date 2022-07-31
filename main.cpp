#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "lib/Server.h"
#include "lib/AtClient.h"
#include "lib/Crypto.h"

// Config file keys
static const std::string ROOT_SERVER_HOST = "rootServerHost";
static const std::string ROOT_SERVER_PORT = "rootServerPort";
static const std::string AT_SIGN = "atSign";
static const std::string PKAM_PEM_FILE = "pkamPemFile";

int main(int argc, char * argv[]) {
    // Check for mandatory config file argument
    if (argc < 2){
        std::cerr << "Usage: "<< argv[0] << " <configfile>" << std::endl;
        exit(1);
    }

    // Open config file for reading
    std::string configFileName = argv[1];
    std::ifstream config(configFileName);
    if(config.fail()){
        std::cerr << "Error: could not open file name " << configFileName << std::endl;
        exit(1);
    }

    // Parse config file and extract relevant data
    nlohmann::json configData = nlohmann::json::parse(config);
    std::string rootHost = configData[ROOT_SERVER_HOST].get<std::string>();
    std::string rootPort = configData[ROOT_SERVER_PORT].get<std::string>();
    AtSign atSign(configData[AT_SIGN].get<std::string>());
    std::string pkamPemFile = configData[PKAM_PEM_FILE].get<std::string>();

    // Create root server object
    Server rootServer(rootHost, rootPort);

    // Get the secondary server for the given atSign
    Server secondaryServer = AtClient::lookupSecondaryForAtSign(rootServer, atSign);

    // Send the `from` command to receive challenge
    std::string challenge = AtClient::from(secondaryServer, atSign);

    // Generate pkam signature using the challenge and pkam private key
    std::vector<unsigned char> signature = Crypto::GenerateRsaSignByFile(challenge, pkamPemFile);
    std::string base64Signature = Crypto::Base64Encode(signature);
    std::cout << "base64Signature sig: " << base64Signature << std::endl;

    // Authenticate using pkam
    std::string pkamResponse = AtClient::pkam(secondaryServer, base64Signature);
    std::cout << "pkamResponse: " << pkamResponse << std::endl;

    // Send `scan` command to retrieve properties of the given atSign that are available for lookup
    std::vector<std::string> properties = AtClient::scan(secondaryServer);
    for (const auto &prop: properties) {
        std::cout << "prop: " << prop << std::endl;
        std::vector<std::string> tokens = Utils::parseResponse(prop);

        // Lookup the proerty of the given atSign using `llookup`
        std::string scanResponse = AtClient::llookup(secondaryServer, prop);
        std::cout << "value: " << scanResponse << std::endl;
    }

    return 0;
}

