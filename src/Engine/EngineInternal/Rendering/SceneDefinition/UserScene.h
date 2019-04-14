#pragma once

#include "GameObject/GameObject.h"
#include "Camera/BaseCamera.h"
#include "Mesh/Mesh.h"

class UserScene {
    public:

        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<GameObject>> objectsToRender;

        UserScene() = default;

        void addObject(const std::shared_ptr<GameObject> & obj) {
            objectsToRender.push_back(obj);
        }
};