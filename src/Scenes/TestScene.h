#pragma once

#include <Engine.h>

#include "../Engine/EngineInternal/Utils/NormalsGenerator.h"

std::shared_ptr<UserScene> testScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-1.2f, 10.0f, 2.0f);

    auto diffuseShader = std::make_shared<Shader>("../resources/shaders/Diffuse.vert", "../resources/shaders/Diffuse.frag");
    auto colorShader = std::make_shared<Shader>("../resources/shaders/Color.vert", "../resources/shaders/Color.frag");

    std::shared_ptr<Mesh> lampMesh = std::make_shared<Mesh>("../resources/models/sphere.obj");
    lampMesh->shader = colorShader;
    lampMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->shader = diffuseShader;
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Surface> surface = std::make_shared<Surface>(100, 100);
    surface->shader = diffuseShader;
    surface->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    auto lampMeshObject = std::make_shared<GameObject>(lampMesh);
    lampMeshObject->transform.scale = glm::vec3(0.1f);
    lampMeshObject->transform.position = *lightPos.get();

    auto cubeObject = std::make_shared<GameObject>(cube);
    cubeObject->transform.position = glm::vec3(0.0f, 0.5f, 0.0f);

    auto surfaceObject = std::make_shared<GameObject>(surface);
    surfaceObject->transform.position = glm::vec3(0.0f, 1.5f, 0.0f);

    scene->addObject(surfaceObject);
    scene->addObject(lampMeshObject);
    scene->addObject(cubeObject);

    //std::shared_ptr<GameObject> normals = NormalsGenerator::generate(surface, colorShader);
    //scene->addObject(normals);

    return scene;
}