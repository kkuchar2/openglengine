#include "MeshPrototype.h"


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