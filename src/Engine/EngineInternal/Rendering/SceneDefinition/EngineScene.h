#pragma once

#include "GameObject/GameObject.h"
#include "Camera/BaseCamera.h"
#include "Mesh/Mesh.h"
#include "EngineObject/EngineObject.h"
#include <chrono>

class EngineScene {
    public:
        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<EngineObject>> objects;

        EngineScene() = default;

        void addObject(const std::shared_ptr<EngineObject> & obj) {
            objects.push_back(obj);
        }
};