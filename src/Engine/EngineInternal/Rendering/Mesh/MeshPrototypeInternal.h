#pragma once

#include <Rendering/Shading/ShaderType.h>
#include <Component.h>
#include <memory>

#include "MeshType.h"

class MeshPrototypeInternal : public Component {
    public:
        MeshType meshType = OTHER;
        ShaderType shaderType = COLOR;

        MeshPrototypeInternal(const MeshType & meshType, const ShaderType & shaderType);

        void prepare();

};

class MeshPrototype : public std::shared_ptr<MeshPrototypeInternal> {
    public :
        static std::shared_ptr<MeshPrototypeInternal> of(const MeshType & meshType, const ShaderType & shaderType) {
            return std::make_shared<MeshPrototypeInternal>(meshType, shaderType);
        }
};
