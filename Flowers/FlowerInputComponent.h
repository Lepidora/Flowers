#pragma once

//Engine includes
#include <InputComponent.h>

using namespace Xylena;

class FlowerInputComponent: public InputComponent {
    
private:
    int flowerCount;
public:
    
    FlowerInputComponent() { init(); }
    
    void init();
    
    void process(GameObject *gameObject);
};
