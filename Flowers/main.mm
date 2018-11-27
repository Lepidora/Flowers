//
//  main.mm
//  Flowers
//
//  Created by Mia on 24/11/2018.
//  Copyright © 2018 Mia. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "Flowers.h"

//Engine Includes
#include <Engine.h>
#include <Game.h>

int main(int argc, const char * argv[]) {
    Engine::initialize(GamePtr(new Flowers()));
    Engine::run();
}
