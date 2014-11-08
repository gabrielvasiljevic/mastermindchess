#ifndef _CONFDAO
#define _CONFDAO
#include <iostream>
#include <map>
#include <fstream>
#include "utility.h"

#ifndef configurationDAO
#define configurationDAO ConfigurationDAO::getInstance()
#endif

class ConfigurationDAO{
    public:
        static ConfigurationDAO& getInstance();

        int getPort();
        int getConsole();
        std::string getServer();

        void setServer(std::string _server);


    private:
        static ConfigurationDAO* instance;
        ConfigurationDAO(ConfigurationDAO const&);
        void operator=(ConfigurationDAO const&);

        int port;
        int console;
        std::string server;
        std::map<std::string, std::string> options;

        void loadConfiguration();
        void parse(std::ifstream & cfgfile);

        ConfigurationDAO(){
            loadConfiguration();
        };


};

#endif // _CONFDAO
