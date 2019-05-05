#include "GameObjectFactory.h"

std::shared_ptr<GameObject> GameObjectFactory::cube(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = GameObject::create(position, rotation, scale);
    auto proto = MeshComponent::of(CUBE, PHONG, color);
    obj->addComponent(proto);
    return obj;
}

std::shared_ptr<GameObject> GameObjectFactory::point(
        const glm::vec3 & position,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = GameObject::create(position);
    obj->instanced = true;
    auto proto = MeshComponent::of(POINT, AMBIENT, color);
    obj->addComponent(proto);
}

std::shared_ptr<GameObject> GameObjectFactory::quad(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = GameObject::create(position, rotation, scale);
    obj->instanced = true;
    auto proto = MeshComponent::of(QUAD, AMBIENT, color);
    obj->addComponent(proto);
    return obj;
}

std::shared_ptr<GameObject> GameObjectFactory::model(
        const char * path,
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = GameObject::create(position, rotation, scale);
    obj->instanced = true;
    auto proto = MeshComponent::of(path, PHONG, color);
    obj->addComponent(proto);
    return obj;
}

std::shared_ptr<GameObject> GameObjectFactory::bunny(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    return GameObjectFactory::model("../resources/models/bunny.obj", position,rotation, scale, color);
}

std::shared_ptr<GameObject> GameObjectFactory::sphere(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    return GameObjectFactory::model("../resources/models/sphere.obj", position,rotation, scale, color);
}

std::shared_ptr<GameObject> GameObjectFactory::suzanne(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    return GameObjectFactory::model("../resources/models/suzanne.obj", position,rotation, scale, color);
}

std::shared_ptr<GameObject> GameObjectFactory::teapot(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    return GameObjectFactory::model("../resources/models/teapot.obj", position,rotation, scale, color);
}

std::shared_ptr<GameObject> GameObjectFactory::surface(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = GameObject::create(position);

    auto surfaceProto = SurfaceMeshComponent::of(PHONG, color);
    surfaceProto->width = scale.x;
    surfaceProto->height = scale.y;


    return obj;
}
