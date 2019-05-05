#pragma once

#include <Components/MeshComponent/MeshComponent.h>
#include <glm/glm/glm.hpp>

class SkyboxPrototype : public MeshComponent {

    public:
        std::vector<std::string> paths;

        SkyboxPrototype() : MeshComponent() {
            meshType = SKYBOX;
            shaderType = TEXTURE_CUBE;
        }

};