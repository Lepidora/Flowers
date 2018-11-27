#pragma once

//System includes
#include <vector>

//Engine includes
#include <GameObject.h>

//Local includes
#include "Flower.h"
#include "PerlinNoise.h"

using namespace Xylena;

class FlowerSpawner: public GameObject {
    
private:
    
    int flowerCount;
    
    int tickCount;
    
    std::vector<Flower> flowers;
    
    PerlinNoise perlin;
    
    void generateFlowers();
    
public:
    
    FlowerSpawner(int _flowerCount);
    
    void setFlowerCount(int _flowerCount);
    int getFlowerCount() { return flowerCount; }
    
    std::vector<Flower> getFlowers() { return flowers; }
    
    void update();
    
    static bool crazy;
};
