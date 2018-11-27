#pragma once

//Engine includes
#include <Texture.h>

//System includes
#include <string>
#include <map>

using namespace Xylena;

class Textures {
private:
    static TexturePtr placeholder;
    static std::map<std::string, TexturePtr> textureMap;
public:
    static void loadTexture(std::string name, std::string location);
    static TexturePtr getTexture(std::string name);
};