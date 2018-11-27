#pragma once

//System includes
#include <memory>

//Library includes
#include <Texture.h>

using namespace Xylena;

class Flower {
    
private:
    
public:
    TexturePtr texture;
    int index;
    float x;
    float y;
    float xOffset;
    float yOffset;
    float angle;
    float size;
};

typedef std::shared_ptr<Flower> FlowerPtr;
