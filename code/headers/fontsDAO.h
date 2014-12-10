#ifndef _FONTDAO
#define _FONTDAO
#include <iostream>
#include <map>
#include <fstream>
#include "utility.h"

#ifndef fontsDAO
#define fontsDAO FontsDAO::getInstance()
#endif

class FontsDAO{
    public:
        static FontsDAO& getInstance();
        sf::Font getFont(std::string fontName);

    private:
        static ConfigurationDAO* instance;
        ConfigurationDAO(ConfigurationDAO const&);
        void operator=(ConfigurationDAO const&);

        sf::Font Carbon;
        sf::Font Anilin;
        std::map<std::string, std::string> fonts;

        void loadFonts();
        void parse(std::ifstream & cfgfile);

        FontsDAO(){
            loadFonts();
        };


};

#endif // _FONTDAO

