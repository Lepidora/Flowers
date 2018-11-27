#include "Field.h"

//Engine includes
#include <StageCamera.h>
#include <Textures.h>

//Local includes
#include "FlowerSpawner.h"

Field::Field() {
    
    load();
    
    StageCameraPtr stageCamera(new StageCamera);
    
    Coordinate minimum(0, 0, 0);
    Coordinate maximum(1280, 720, 0);
    
    Bounds cameraBounds(minimum, maximum);
    stageCamera->setBounds(cameraBounds);
    
    stageCamera->setPosition(1280/2, 720/2);
    
    setActiveCamera(stageCamera);
    
    TexturePtr daisy = Textures::getTexture("flower");
    
    int flowerCount = 12000;
    
    if (FlowerSpawner::crazy) {
        flowerCount = 8000;
    }
    
    FlowerSpawner *fs = new FlowerSpawner(flowerCount);
    fs->setFlowerCount(flowerCount);
    
    fs->setSize(32, 32);
    fs->setPosition(200, 200);
    
    addObject(GameObjectPtr(fs));
    
    /*for (int i = 0; i < flowerCount; i++) {
        
        GameObjectPtr spawner = GameObjectPtr(new FlowerSpawner(1));
        
        spawner->setSize(32, 32);
        spawner->setRotation(rand() % 360);
        
        spawner->setPosition(rand() % 1280, rand() % 720);
        
        spawner->setTexture(daisy);
        
        addObject(spawner);
    }*/

    
    
    
}

void Field::load() {
    
    Textures::loadTexture("flower", "flowers.png");
    
}

