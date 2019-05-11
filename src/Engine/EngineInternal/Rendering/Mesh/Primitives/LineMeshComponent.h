#pragma once

#include <Components/MeshComponent/MeshComponent.h>
#include <glm/glm/glm.hpp>

class LineMeshComponent : public MeshComponent {

    public:
        glm::vec3 start = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 end = glm::vec3(1.0f, 1.0f, 1.0f);

        LineMeshComponent() : MeshComponent() {
            meshType = LINE;
        }
};