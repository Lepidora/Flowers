#include "FlowerSpawner.h"

//Engine includes
#include <SpriteRenderComponent.h>
#include <Input.h>

//Local includes
#include "Textures.h"
#include "FlowerRenderComponent.h"
#include "FlowerInputComponent.h"

using namespace Xylena;

bool FlowerSpawner::crazy = false;

FlowerSpawner::FlowerSpawner(int _flowers) {
    
    setInputComponent(new FlowerInputComponent);
    
    flowerCount = _flowers;
    
    tickCount = 0;
    
    int total = 1280 * 720;
    
    perlin = PerlinNoise(rand());
    
    generateFlowers();
    
    setRenderComponent(FlowerRenderComponent::getComponent());
    
}

void FlowerSpawner::setFlowerCount(int _flowerCount) {
    
    flowerCount = _flowerCount;
    
    generateFlowers();    
}

void FlowerSpawner::generateFlowers() {
    
    flowers.clear();
    
    TexturePtr texture = Textures::getTexture("flower");
    
    for (int i = 0; i < flowerCount; i++) {
        
        Flower flower;
        flower.texture = texture;
        
        flower.index = rand() % 8;
        
        int randX = rand() % 1280;
        int randY = rand() % 720;
        
        float normalX = randX / 1280.0f;
        float normalY = randY / 720.0f;
        
        float scaleX = normalX * 4;
        float scaleY = normalY * 4;
        
        float shiftX = scaleX - 1;
        float shiftY = scaleY - 1;
        
        flower.x = shiftX;
        flower.y = shiftY;
        
        flower.angle = rand()%360;
        
        flower.size = 32 + (rand() % 8 - 4);
        
        flowers.push_back(flower);
    }
}

void FlowerSpawner::update() {
    
    getInputComponent()->process(this);
    
    for (int i = 0; i < flowers.size(); i++) {
        
        Flower &flower = flowers[i];
        
        if (crazy) {
            
            float scale = tickCount / 1000.0;
            
            float xPos = flower.x + scale;
            float yPos = flower.y + scale;
            
            double offset = (perlin.noise(xPos, yPos, 0.0) * 2) - 1;
            
            flower.xOffset = (float)offset;
            flower.yOffset = (float)offset;
            
        } else {
            
            float scale = tickCount / 200.0;
            
            float xPos = (flower.x * 2 + scale);
            float yPos = (flower.y / 2 + scale);
            
            double offset = ((perlin.noise(xPos, yPos, 0.0) * 2) - 1) / 48;
            
            flower.xOffset = (float)offset;
            flower.yOffset = 0;
        }
    }
    
    
    tickCount++;
}
