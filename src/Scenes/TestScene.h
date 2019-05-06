#pragma once

#include <Engine/Engine.h>

#include "Utils/NormalsGenerator/NormalsGenerator.h"

std::shared_ptr<Scene> testScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-1.2f, 10.0f, 2.0f);

    auto diffuseShader = std::make_shared<Shader>("../resources/shaders/DiffuseInstanced.vert", "../resources/shaders/DiffuseInstanced.frag");
    auto colorShader = std::make_shared<Shader>("../resources/shaders/ColorInstanced.vert", "../resources/shaders/ColorInstanced.frag");

    std::shared_ptr<Mesh> lampMesh = std::make_shared<Mesh>("../resources/models/sphere.obj");
    lampMesh->shader = colorShader;
    lampMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setglm::vec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->shader = diffuseShader;
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setglm::vec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Surface> surface = std::make_shared<Surface>(100, 100);
    surface->shader = diffuseShader;
    surface->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setglm::vec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
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

    scene->addChild(surfaceObject);
    scene->addChild(lampMeshObject);
    scene->addChild(cubeObject);

    //std::shared_ptr<GameObject> normals = NormalsGenerator::generate(surface, colorShader);
    //scene->addChild(normals);

    return scene;
}