#pragma once

#include <iostream>
#include "BehaviourComponent.h"

class RotatingBehaviour : public BehaviourComponent {

        void Update() override {
            // TODO: Do not cast every frame
            auto * go = reinterpret_cast<GameObject *>(gameObject);
            auto t = go->transform;
            auto oldRotation = t.rotation;
            go->transform.rotation = glm::vec3(oldRotation.x, oldRotation.y + 0.1f, oldRotation.z);
            go->transform.modelMatrix = MatrixUtils::modelMatrix(
                    go->transform.scale, go->transform.position,
                    MatrixUtils::rotationMatrix(go->transform.rotation));
        }
};