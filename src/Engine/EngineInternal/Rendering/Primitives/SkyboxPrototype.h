#pragma once

#include <Rendering/Mesh/MeshPrototype.h>
#include <glm/glm/glm.hpp>

class SkyboxPrototype : public MeshPrototype {

    public:
        std::vector<std::string> paths;

        SkyboxPrototype() : MeshPrototype() {
            meshType = SKYBOX;
            shaderType = TEXTURE_CUBE;
        }

};