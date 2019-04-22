#pragma once

#include <Behaviour/RotatingBehaviour.h>

std::shared_ptr<GameObject> object(const char * path, const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = size;
    obj->transform.position = glm::vec3(position);

    float r = 0.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(90.0f-0.0f)));
    obj->transform.rotation = glm::vec3(0.0f, r, 0.0f);

    auto proto = MeshPrototype::of(path, DIFFUSE, color);
    proto->instanced = true;
    obj->addComponent(proto);
    obj->addComponent(std::make_shared<RotatingBehaviour>());
    return obj;
}


std::shared_ptr<GameObject> cube(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = size;
    obj->transform.position = glm::vec3(position);

    float r = 0.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(90.0f-0.0f)));
    obj->transform.rotation = glm::vec3(0.0f, r, 0.0f);

    auto proto = MeshPrototype::of(CUBE, DIFFUSE, color);
    proto->instanced = true;
    obj->addComponent(proto);
    obj->addComponent(std::make_shared<RotatingBehaviour>());
    return obj;
}

std::shared_ptr<GameObject> point(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = size;
    obj->transform.position = glm::vec3(position);

    float r = 0.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(90.0f-0.0f)));
    obj->transform.rotation = glm::vec3(0.0f, r, 0.0f);

    auto proto = MeshPrototype::of(POINT, COLOR, color);
    proto->instanced = true;
    obj->addComponent(proto);
    obj->addComponent(std::make_shared<RotatingBehaviour>());
    return obj;
}

std::shared_ptr<GameObject> quad(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = size;
    obj->transform.position = glm::vec3(position);

    float r = 0.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(90.0f-0.0f)));
    obj->transform.rotation = glm::vec3(0.0f, r, 0.0f);

    auto proto = MeshPrototype::of(QUAD, COLOR, color);
    proto->instanced = true;
    obj->addComponent(proto);
    obj->addComponent(std::make_shared<RotatingBehaviour>());
    return obj;
}

std::shared_ptr<GameObject> sphere(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    return object("../resources/models/sphere.obj", size, position, color);
}

std::shared_ptr<GameObject> bunny(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    auto obj = object("../resources/models/bunny.obj", size, position, color);
    obj->addComponent(std::make_shared<RotatingBehaviour>());
    return obj;
}

std::shared_ptr<GameObject> suzanne(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    return object("../resources/models/suzanne.obj", size, position, color);
}

std::shared_ptr<GameObject> teapot(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    return object("../resources/models/teapot.obj", size, position, color);
}

std::shared_ptr<GameObject> surface(const glm::vec2 & size, const glm::vec3 & position, const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.position = glm::vec3(position);

    auto surfaceProto = SurfacePrototype::of(DIFFUSE, color);
    surfaceProto->width = size.x;
    surfaceProto->height = size.y;
    obj->addComponent(surfaceProto);
    return obj;
}

std::shared_ptr<GameObject> line(glm::vec3 start, glm::vec3 end, const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->addComponent(MeshPrototype::of(LINE, COLOR, color));
    return obj;
}