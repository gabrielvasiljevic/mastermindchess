#include "headers/configurationDAO.h"


ConfigurationDAO& ConfigurationDAO::getInstance(){
    static ConfigurationDAO instance;
    return instance;
}

void ConfigurationDAO::loadConfiguration(){
    std::ifstream config {"config.dat"};
    parse(config);
    port = Utility::StringToNumber(options["Port"]);
    server = options["Server"];
    console = Utility::StringToNumber(options["Console"]);
}

void ConfigurationDAO::parse(std::ifstream & cfgfile){
    std::string id, eq, val;

    while(cfgfile >> id >> val){
      if (id[0] == '#') continue;  // skip comments
      //if (eq != "=") throw std::runtime_error("Parse error");

      options[id] = val;
    }
}

std::string ConfigurationDAO::getServer(){
    return server;
}

int ConfigurationDAO::getConsole(){
    return console;
}

int ConfigurationDAO::getPort(){
    return port;
}

void ConfigurationDAO::setServer(std::string _server){
    ofstream output{"config.dat"};
    output  << "Server "    << _server << "\n"
            << "Port "      << port    << "\n"
            << "Console "   << console;
}

