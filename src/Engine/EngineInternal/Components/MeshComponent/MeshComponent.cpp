#include "MeshComponent.h"

MeshComponent::MeshComponent() = default;

MeshComponent::MeshComponent(const MeshType & meshType) {
    this->meshType = meshType;
}

MeshComponent::MeshComponent(const std::string & path) {
    this->path = path;
    this->meshType = RESOURCE;
}

std::string MeshComponent::getMeshIdText() {
    switch(meshType) {
        case LINE: return "line";
        case QUAD: return "quad";
        case CUBE: return "cube";
        case SURFACE: return "surface";
        case RESOURCE: return path;
        case NONE: return "";
        default: return "";
    }
}