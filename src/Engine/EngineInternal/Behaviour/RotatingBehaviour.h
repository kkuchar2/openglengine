#pragma once

#include <iostream>
#include "BehaviourComponent.h"

class RotatingBehaviour : public BehaviourComponent {

        void Update() override {
            auto * go = reinterpret_cast<GameObject *>(gameObject);
            auto oldRotation = go->transform.rotation;
            go->transform.rotation = glm::vec3(oldRotation.x, oldRotation.y + 0.02f, oldRotation.z);

            auto rotation = go->transform.rotation;
        }
};