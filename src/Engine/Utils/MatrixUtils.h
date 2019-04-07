#pragma once

#include <glm/glm.hpp>

class MatrixUtils {
    public:
        static glm::mat4 scaleMatrix(glm::vec3 scale) {
            return glm::mat4(
                    scale.x, 0.0, 0.0, 0.0,
                    0.0, scale.y, 0.0, 0.0,
                    0.0, 0.0, scale.z, 0.0,
                    0.0, 0.0, 0.0, 1.0
            );
        }

        static glm::mat4 rotationMatrix(glm::vec3 rotation) {
            glm::mat4 rotMatX = rotationMatrix(glm::vec3(1.0, 0.0, 0.0), rotation.x);
            glm::mat4 rotMatY = rotationMatrix(glm::vec3(0.0, 1.0, 0.0), rotation.y);
            glm::mat4 rotMatZ = rotationMatrix(glm::vec3(0.0, 0.0, 1.0), rotation.z);
            return rotMatX * rotMatY * rotMatZ;
        }

        static glm::mat4 rotationMatrix(glm::vec3 axis, float angle) {
            axis = normalize(axis);

            float s = static_cast<float>(sin(angle));
            float c = static_cast<float>(cos(angle));
            float oc = static_cast<float>(1.0 - c);

            return glm::mat4(
                    oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s, 0.0,
                    oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s, 0.0,
                    oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c, 0.0,
                    0.0, 0.0, 0.0, 1.0);
        }
};