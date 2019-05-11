#pragma once

#include <string>
#include <memory>

#include "../Component.h"
#include "../../Rendering/Shading/ShaderType.h"
#include "../../Rendering/Mesh/MeshType.h"

class MeshComponent : public Component {

    public:

        MeshType meshType = NONE;

        std::string path;

        MeshComponent();

        MeshComponent(const MeshType & meshType);

        MeshComponent(const std::string & path);

        std::string getMeshIdText();
};