#include "Flowers.h"

#include <stdio.h>

//Engine includes
#include <WindowHandler.h>
#include <StageHandler.h>
#include <Render.h>
#include <Stage.h>

//Local includes
#include "Field.h"

void Flowers::initialize() {
    
    WindowHandler::openMainWindow("Flowers", 1280, 720, WindowType::WINDOWED);
    WindowHandler::getMainWindow()->vsync(true);
    
    Render::setBackgroundColor(67, 176, 22, 255);
    
    Field *field = new Field();
    
    StageHandler::setCurrentStage(StagePtr(field));
    
}

void Flowers::onStop() {
    printf("Finished running!");
}
