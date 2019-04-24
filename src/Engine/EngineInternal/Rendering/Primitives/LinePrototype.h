#pragma once

#include <Rendering/Mesh/MeshPrototype.h>
#include <glm/glm/glm.hpp>

class LinePrototype : public MeshPrototype {

    public:
        glm::vec3 start = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 end = glm::vec3(1.0f, 1.0f, 1.0f);

        LinePrototype() : MeshPrototype() {
            meshType = LINE;
            shaderType = AMBIENT;
        }

};