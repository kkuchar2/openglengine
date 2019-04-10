#pragma once

#include <Rendering/Shading/ShaderType.h>
#include <Component.h>
#include "MeshType.h"

class MeshPrototype : public Component {
    public:
        MeshType meshType = OTHER;
        ShaderType shaderType = COLOR;
        MeshPrototype() {}

        void prepare() {

        }
};