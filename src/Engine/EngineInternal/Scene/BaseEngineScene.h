#pragma once

#include <Primitives/Quad.h>
#include <Rendering/Primitives/LinePrototype.h>
#include <Rendering/Primitives/SkyboxPrototype.h>

#include "Shading/ShaderPool.h"

#include "Scene.h"

std::shared_ptr<Scene> baseEngineScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<SkyboxPrototype> skybox = std::make_shared<SkyboxPrototype>();
    skybox->paths = {
        "../resources/textures/skybox/right.jpg",
        "../resources/textures/skybox/left.jpg",
        "../resources/textures/skybox/top.jpg",
        "../resources/textures/skybox/bottom.jpg",
        "../resources/textures/skybox/front.jpg",
        "../resources/textures/skybox/back.jpg"
    };
    skybox->disableBoundingBox = true;

    std::shared_ptr<GameObject> skyBoxObject = std::make_shared<GameObject>();
    skyBoxObject->addComponent(skybox);
    skyBoxObject->transform.scale = glm::vec3(10000.0f);

    std::shared_ptr<MeshComponent> gridQuad = std::make_shared<MeshComponent>();
    gridQuad->meshType = QUAD;
    gridQuad->shaderType = GRID;
    gridQuad->texture = "../resources/textures/texture_white.bmp";
    gridQuad->disableBoundingBox = true;

    std::shared_ptr<GameObject> gridObject = std::make_shared<GameObject>();
    gridObject->addComponent(gridQuad);
    gridObject->transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);
    gridObject->transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);

    std::shared_ptr<LinePrototype> axisX = std::make_shared<LinePrototype>();
    axisX->shaderType = AMBIENT;
    axisX->start = glm::vec3(-20.0f, 0.0f, 0.0f);
    axisX->end = glm::vec3(20.0f, 0.0f, 0.0f);
    axisX->color = glm::vec4(0.0f, 1.0, 0.0, 1.0);
    axisX->disableBoundingBox = true;
    std::shared_ptr<GameObject> axisXObject = std::make_shared<GameObject>();
    axisXObject->addComponent(axisX);

    std::shared_ptr<LinePrototype> axisY = std::make_shared<LinePrototype>();
    axisY->shaderType = AMBIENT;
    axisY->start = glm::vec3(0.0f, -20.0f, 0.0f);
    axisY->end = glm::vec3(0.0f, 20.0f, 0.0f);
    axisY->color = glm::vec4(1.0f, 0.0, 0.0, 1.0);
    axisY->disableBoundingBox = true;
    std::shared_ptr<GameObject> axisYObject = std::make_shared<GameObject>();
    axisYObject->addComponent(axisY);

    std::shared_ptr<LinePrototype> axisZ = std::make_shared<LinePrototype>();
    axisZ->shaderType = AMBIENT;
    axisZ->start = glm::vec3(0.0f, 0.0f, -20.0f);
    axisZ->end = glm::vec3(0.0f, 0.0f, 20.0f);
    axisZ->color = glm::vec4(0.0f, 0.0, 1.0, 1.0);
    axisZ->disableBoundingBox = true;
    std::shared_ptr<GameObject> axisZObject = std::make_shared<GameObject>();
    axisZObject->addComponent(axisZ);

    scene->addChild(skyBoxObject);
    scene->addChild(axisXObject);
    scene->addChild(axisYObject);
    scene->addChild(axisZObject);
    scene->addChild(gridObject);

    return scene;
}