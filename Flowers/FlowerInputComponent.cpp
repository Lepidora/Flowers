#include "FlowerInputComponent.h"

//Engine includes
#include <GameObject.h>
#include <StageHandler.h>
#include <Stage.h>
#include <StageCamera.h>

//Local includes
#include "FlowerSpawner.h"

void FlowerInputComponent::process(GameObject *gameObject) {
    
    FlowerSpawner *spawner = dynamic_cast<FlowerSpawner *>(gameObject);
    
    if (spawner == nullptr) {
        return;
    }
    
    while (!inputQueue.empty()) {
        //break;
        InputEvent input = inputQueue.front();
        
        KeyCode code = input.getKeyCode();
        KeyStatus status = input.getKeyStatus();
        
        if (code == KEY_SPACE) {
            if (status == KEY_RELEASE) {
                FlowerSpawner::crazy = !FlowerSpawner::crazy;
            }
        }
        
        if (code == KEY_MINUS) {
            if (status == KEY_RELEASE) {
                
                StageCameraPtr camera = StageHandler::getCurrentStage()->getActiveCamera();
                
                camera->setScalingFactor(camera->getScalingFactor() * 2);
            }
        }
        
        if (code == KEY_EQUAL) {
            if (status == KEY_RELEASE) {
                
                StageCameraPtr camera = StageHandler::getCurrentStage()->getActiveCamera();
                
                camera->setScalingFactor(camera->getScalingFactor() / 2);
            }
        }
        
        if (code == KEY_UP) {
            if (status == KEY_RELEASE) {
                
                flowerCount *= 2;
                
                printf("%d flowers\n", flowerCount);
                
                spawner->setFlowerCount(flowerCount);
            }
        }
        
        if (code == KEY_DOWN) {
            if (status == KEY_RELEASE) {
                
                flowerCount /= 2;
                
                if (flowerCount <= 1) {
                    flowerCount = 1;
                }
                
                printf("%d flowers\n", flowerCount);
                
                spawner->setFlowerCount(flowerCount);
            }
        }
        
        inputQueue.pop();
    }
}

void FlowerInputComponent::init() {
    
    flowerCount = 12000;
    
    Input::registerEvent(this, InputEvent(KEY_SPACE, KEY_RELEASE));
    Input::registerEvent(this, InputEvent(KEY_MINUS, KEY_RELEASE));
    Input::registerEvent(this, InputEvent(KEY_EQUAL, KEY_RELEASE));
    Input::registerEvent(this, InputEvent(KEY_UP, KEY_RELEASE));
    Input::registerEvent(this, InputEvent(KEY_DOWN, KEY_RELEASE));
}
