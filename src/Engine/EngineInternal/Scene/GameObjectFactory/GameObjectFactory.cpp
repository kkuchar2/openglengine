#include "GameObjectFactory.h"



std::shared_ptr<GameObject> GameObjectFactory::cube(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(position, rotation, scale);

    auto mesh = std::make_shared<MeshComponent>(CUBE);

    auto meshRenderer = std::make_shared<MeshRenderer>();
    meshRenderer->shaderType = PHONG;
    meshRenderer->color = color;
    meshRenderer->instanced = true;

    obj->addComponent(mesh);
    obj->addComponent(meshRenderer);
    return obj;
}

std::shared_ptr<GameObject> GameObjectFactory::point(
        const glm::vec3 & position,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(position);

    auto mesh = std::make_shared<MeshComponent>(POINT);
    auto meshRenderer = std::make_shared<MeshRenderer>();
    meshRenderer->shaderType = AMBIENT;
    meshRenderer->color = color;
    meshRenderer->instanced = true;

    obj->addComponent(mesh);
    obj->addComponent(meshRenderer);
}

std::shared_ptr<GameObject> GameObjectFactory::quad(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(position, rotation, scale);

    auto mesh = std::make_shared<MeshComponent>(QUAD);
    auto meshRenderer = std::make_shared<MeshRenderer>();
    meshRenderer->shaderType = AMBIENT;
    meshRenderer->color = color;
    meshRenderer->instanced = true;
    obj->addComponent(mesh);
    obj->addComponent(meshRenderer);

    return obj;
}

std::shared_ptr<GameObject> GameObjectFactory::model(
        const char * path,
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(position, rotation, scale);
    auto mesh = std::make_shared<MeshComponent>(path);
    auto meshRenderer = std::make_shared<MeshRenderer>();
    meshRenderer->shaderType = PHONG;
    meshRenderer->color = color;
    meshRenderer->instanced = true;
    obj->addComponent(mesh);
    obj->addComponent(meshRenderer);
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

std::shared_ptr<GameObject> GameObjectFactory::cone(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    return GameObjectFactory::model("../resources/models/cone.obj", position,rotation, scale, color);
}

std::shared_ptr<GameObject> GameObjectFactory::surface(
        const glm::vec3 & position,
        const glm::vec3 & rotation,
        const glm::vec3 & scale,
        const glm::vec4 & color) {

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(position);

    auto mesh = SurfaceMeshComponent::create();
    mesh->width = scale.x;
    mesh->height = scale.y;

    auto meshRenderer = std::make_shared<MeshRenderer>();
    meshRenderer->shaderType = PHONG;
    meshRenderer->color = color;

    obj->addComponent(mesh);
    obj->addComponent(meshRenderer);

    return obj;
}

std::shared_ptr<GameObject>
GameObjectFactory::point(
        const glm::vec3 & pos,
        const glm::vec3 & rot,
        const glm::vec3 & scale,
        const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(pos, rot, scale);

    auto mesh = std::make_shared<MeshComponent>(POINT);
    auto meshRenderer = std::make_shared<MeshRenderer>();

    meshRenderer->renderingMode = GL_POINTS;
    meshRenderer->shaderType = AMBIENT;
    meshRenderer->color = color;
    meshRenderer->instanced = true;

    obj->addComponent(mesh);
    obj->addComponent(meshRenderer);

    glPointSize(5.0f);

    return obj;
}
