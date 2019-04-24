#pragma once

#include "../../Utils/MatrixUtils.h"

class Transform {

    public:
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

        glm::mat4x4 rotationMatrix = glm::mat4x4();
        glm::mat4x4 scaleMatrix = glm::mat4x4();
        glm::mat4x4 positionMatrix = glm::mat4x4();

        glm::mat4x4 modelMatrix = glm::mat4x4();

        void calculatePositionRotationScaleMatrices() {
            positionMatrix = MatrixUtils::translationMatrix(position);
            scaleMatrix = MatrixUtils::scaleMatrix(scale);
            rotationMatrix = MatrixUtils::rotationMatrix(rotation);
        }

        void calculateModelMatrix() {
            modelMatrix = positionMatrix * rotationMatrix * scaleMatrix;
        }
};