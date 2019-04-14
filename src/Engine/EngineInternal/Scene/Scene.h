#pragma once

#include "GameObject/GameObject.h"
#include "../Camera/PerspectiveCamera.h"

class Scene {
    public:

        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<GameObject>> objectsToRender;

        Scene() = default;

        void addObject(std::shared_ptr<GameObject> & obj) {
            objectsToRender.push_back(obj);
        }
};