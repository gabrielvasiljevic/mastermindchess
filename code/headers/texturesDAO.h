#ifndef _TEXTURESDAO
#define _TEXTURESDAO
#include <iostream>
#include <map>
#include <fstream>
#include "utility.h"

#ifndef texturesDAO
#define texturesDAO TexturesDAO::getInstance()
#endif

class TexturesDAO{
    public:
        static TexturesDAO& getInstance();

        sf::Texture getTexture(std::string textureName);

    private:
        static TexturesDAO* instance;
        TexturesDAO(TexturesDAO const&);
        void operator=(TexturesDAO const&);


        std::map<std::string, std::string> textures;

        std::vector<sf::Texture*> backgroundsTextures;
        std::vector<sf::Texture*> piecesTextures;
        std::vector<sf::Texture*> piecesTextures;


        void loadTextures();

        TexturesDAO(){
            loadTextures();
        };


};

#endif // _TEXTURESDAO


