#pragma once

#include <Engine/Engine.h>

std::shared_ptr<Scene> testCubeScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<MeshComponent> cubeMeshProto = std::make_shared<MeshComponent>();
    cubeMeshProto->meshType = CUBE;
    cubeMeshProto->shaderType = PHONG;
    cubeMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 0.5f);

    std::shared_ptr<GameObject> cubeObject = std::make_shared<GameObject>();
    cubeObject->transform.position = glm::vec3(0.0f, 1.0f, 0.0f);
    cubeObject->transform.rotation = glm::vec3(5.0f, 5.0f, 5.0f);
    cubeObject->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    cubeObject->addComponent(cubeMeshProto);

    cubeObject->addComponent(std::make_shared<Rotator>());

    scene->addChild(cubeObject);

    return scene;
}