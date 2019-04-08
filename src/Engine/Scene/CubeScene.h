#pragma once

#include "../Engine.h"
#include "../Utils/NormalsGenerator.h"

std::shared_ptr<UserScene> cubeScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-2.0f, 2.0f, 2.0f);

    std::shared_ptr<Mesh> lampMesh = std::make_shared<Mesh>("../resources/models/sphere.obj");
    lampMesh->shader = ShaderPool::Instance().colorShader;
    lampMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->shader = ShaderPool::Instance().diffuseShader;
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    auto lampObject = std::make_shared<GameObject>(lampMesh);

    lampObject->transform.scale = glm::vec3(0.1f);
    lampObject->transform.position = *lightPos.get();
    scene->addObject(lampObject);

    auto cubeObject = std::make_shared<GameObject>(cube);
    cubeObject->transform.position = glm::vec3(0.0f, 0.5f, 0.0f);

    scene->addObject(cubeObject);

    std::shared_ptr<GameObject> normals = NormalsGenerator::generate(cubeObject->transform, cube, ShaderPool::Instance().colorShader);
    scene->addObject(normals);

    return scene;
}