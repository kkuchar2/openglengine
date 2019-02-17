#ifndef OPENGL_LIGHTPOSITIONUPDATER_H
#define OPENGL_LIGHTPOSITIONUPDATER_H

#include <iostream>
#include "Engine/Base/Component.h"

class LightPositionUpdater : Component {

    void Update() override {
        std::cout << "Light position updater" << std::endl;
    }
};

#endif //OPENGL_LIGHTPOSITIONUPDATER_H
