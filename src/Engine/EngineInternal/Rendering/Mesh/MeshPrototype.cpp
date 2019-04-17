#include "MeshPrototype.h"

MeshPrototype::MeshPrototype() = default;

MeshPrototype::MeshPrototype(const MeshType & meshType, const ShaderType & shaderType, const glm::vec4 & color) {
    this->meshType = meshType;
    this->shaderType = shaderType;
    this->color = color;
}

MeshPrototype::MeshPrototype(const char * path, const ShaderType & shaderType, const glm::vec4 & color) {
    this->path = path;
    this->meshType = RESOURCE;
    this->shaderType = shaderType;
    this->color = color;
}

const char * MeshPrototype::getMeshType() {

    switch(meshType) {
        case LINE: return "LINE";
        case QUAD: return "QUAD";
        case CUBE: return "CUBE";
        case SURFACE: return "SURFACE";
        case SKYBOX: return "SKYBOX";
        case RESOURCE: return path;
        case NONE: return "";
        default: return "";

    }
}
