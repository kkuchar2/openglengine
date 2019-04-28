#pragma once

#include "../../Utils/MatrixUtils.h"
#include <vector>
#include <iomanip>

class Transform {

    public:
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
        glm::vec3 pivot = glm::vec3(0.0f);

        glm::mat4x4 rotationMatrix = glm::mat4x4();
        glm::mat4x4 scaleMatrix = glm::mat4x4();
        glm::mat4x4 positionMatrix = glm::mat4x4();
        glm::mat4x4 modelMatrix = glm::mat4x4();

        int index = 0;

        std::vector<glm::mat4x4> * matricesRef;

        void init() {
            positionMatrix = MatrixUtils::translationMatrix(position);
            scaleMatrix = MatrixUtils::scaleMatrix(scale);
            rotationMatrix = MatrixUtils::rotationMatrix(rotation);
        }

        void calculateModelMatrix() {
            (*matricesRef)[index] = positionMatrix * rotationMatrix  * scaleMatrix;
        }

        void calculateModelMatrix2() {
            glm::mat4x4 pivotMat = MatrixUtils::translationMatrix(pivot);
            (*matricesRef)[index] = positionMatrix * rotationMatrix * pivotMat * scaleMatrix;
        }
};