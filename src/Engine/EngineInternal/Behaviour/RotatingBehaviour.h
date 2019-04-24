#pragma once

#include <iostream>
#include "BehaviourComponent.h"

class RotatingBehaviour : public BehaviourComponent {

        void Start() override {
        }

        void Update() override {
            auto t = gameObject->transform;
            auto oldRotation = t.rotation;
            auto oldPos = t.position;

            gameObject->transform.rotation = glm::vec3(oldRotation.x, oldRotation.y + 0.01f, oldRotation.z);
            gameObject->transform.modelMatrix = MatrixUtils::modelMatrix(
                    gameObject->transform.scale, gameObject->transform.position,
                    MatrixUtils::rotationMatrix(gameObject->transform.rotation));
        }
};