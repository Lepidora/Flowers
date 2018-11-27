#include "Textures.h"

//Engine includes
#include <TextureHandler.h>

TexturePtr Textures::placeholder(new Texture);
std::map<std::string, TexturePtr> Textures::textureMap;

void Textures::loadTexture(std::string name, std::string location) {
    Texture * texturePointer = TextureHandler::createTextureFromFile(location.c_str());
    textureMap.insert(std::pair<std::string, TexturePtr>(name, TexturePtr(texturePointer)));
}

TexturePtr Textures::getTexture(std::string name) {
    
    auto textureSearch = textureMap.find(name);
    
    if (textureSearch != textureMap.end()) {
        return textureMap.find(name)->second;
    } else {
        return placeholder;
    }
}