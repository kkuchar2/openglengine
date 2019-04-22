#pragma once

#include <iostream>
#include "BehaviourComponent.h"

class RotatingBehaviour : public BehaviourComponent {

        void Update() override {
            // TODO: Do not cast every frame
            auto * go = reinterpret_cast<GameObject *>(gameObject);
            auto t = go->transform;
            auto oldRotation = t.rotation;
            auto oldPos = t.position;

            //float HI = 0.05f;
            //float LO = -0.05f;

            //float r1 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            //float r2 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            //float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            //go->transform.position = glm::vec3(oldPos.x +r1, oldPos.y + r2, oldPos.z + r3);

            go->transform.rotation = glm::vec3(oldRotation.x, oldRotation.y + 0.1f, oldRotation.z);
            go->transform.modelMatrix = MatrixUtils::modelMatrix(
                    go->transform.scale, go->transform.position,
                    MatrixUtils::rotationMatrix(go->transform.rotation));
        }
};