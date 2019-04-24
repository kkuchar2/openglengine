#pragma once

#include "GameObject/GameObject.h"
#include "Camera/BaseCamera.h"
#include "Mesh/Mesh.h"

class Scene {
    public:

        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<GameObject>> children;

        Scene() = default;

        void addChild(const std::shared_ptr<GameObject> & child) {
            child->projection = projection;
            children.push_back(child);
        }
};