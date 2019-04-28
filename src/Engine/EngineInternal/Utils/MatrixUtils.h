#pragma once

#include <glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

class MatrixUtils {
    public:

        static glm::mat4 modelMatrix(const glm::vec3 & s, const glm::vec3 & t, const glm::mat4 & r) {
            return glm::mat4(
                    r[0][0] * s.x, r[0][1] * s.x, r[0][2] * s.x, 0,
                    r[1][0] * s.y, r[1][1] * s.y, r[1][2] * s.y, 0,
                    r[2][0] * s.z, r[2][1] * s.z, r[2][2] * s.z, 0,
                    t.x, t.y, t.z, 1.0
            );
        }

        static glm::mat4 scaleMatrix(glm::vec3 scale) {
            return glm::mat4x4(
                    scale.x, 0.0, 0.0, 0.0,
                    0.0, scale.y, 0.0, 0.0,
                    0.0, 0.0, scale.z, 0.0,
                    0.0, 0.0, 0.0, 1.0
            );
        }

        static glm::mat4x4 translationMatrix(const glm::vec3 & p) {
            return glm::mat4x4(
                    1.0, 0.0, 0.0, 0.0,
                    0.0, 1.0, 0.0, 0.0,
                    0.0, 0.0, 1.0, 0.0,
                    p.x, p.y, p.z, 1.0
            );
        }

        static glm::mat4x4 translate(const glm::vec3 & p) {
            return glm::mat4(
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    0.0, 0.0, 0.0, 0.0,
                    p.x, p.y, p.z, 0.0
            );
        }

        static glm::mat4 rotationMatrix(const glm::vec3 & r) {
            float a = cos(r.x);
            float b = sin(r.x);
            float c = cos(r.y);
            float d = sin(r.y);
            float e = cos(r.z);
            float f = sin(r.z);

            return glm::mat4(
                    e * c, f * c, -d, 0.0,
                    -f * a + e * d * b, e * a + f * d * b, c * b, 0.0,
                    f * b + e * d * a, -e * b + f * d * a, c * a, 0.0,
                    0.0f, 0.0f, 0.0f, 1.0f
            );
        }
};