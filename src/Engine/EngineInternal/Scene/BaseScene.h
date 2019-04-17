#pragma once

#include "../Engine.h"
#include "Shading/ShaderPool.h"
#include <Primitives/Quad.h>
#include <Utils/Objects.h>
#include <Rendering/Primitives/LinePrototype.h>
#include <Rendering/Primitives/SkyboxPrototype.h>

std::shared_ptr<UserScene> baseScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    std::shared_ptr<SkyboxPrototype> skybox = std::make_shared<SkyboxPrototype>();
    skybox->paths = {
        "../resources/textures/skybox/right.jpg",
        "../resources/textures/skybox/left.jpg",
        "../resources/textures/skybox/top.jpg",
        "../resources/textures/skybox/bottom.jpg",
        "../resources/textures/skybox/front.jpg",
        "../resources/textures/skybox/back.jpg"
    };

    std::shared_ptr<GameObject> skyBoxObject = std::make_shared<GameObject>(skybox);
    skyBoxObject->transform.scale = glm::vec3(10000.0f);

    std::shared_ptr<MeshPrototype> gridQuad = std::make_shared<MeshPrototype>();
    gridQuad->meshType = QUAD;
    gridQuad->instanced = false;
    gridQuad->shaderType = GRID;
    gridQuad->texture = "../resources/textures/texture_white.bmp";

    std::shared_ptr<GameObject> gridObject = std::make_shared<GameObject>(gridQuad);
    gridObject->transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);
    gridObject->transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);

    std::shared_ptr<LinePrototype> axisX = std::make_shared<LinePrototype>();
    axisX->instanced = false;
    axisX->shaderType = COLOR;
    axisX->start = glm::vec3(-20.0f, 0.0f, 0.0f);
    axisX->end = glm::vec3(20.0f, 0.0f, 0.0f);
    axisX->color = glm::vec4(0.0f, 1.0, 0.0, 1.0);
    std::shared_ptr<GameObject> axisXObject = std::make_shared<GameObject>(axisX);

    std::shared_ptr<LinePrototype> axisY = std::make_shared<LinePrototype>();
    axisY->instanced = false;
    axisY->shaderType = COLOR;
    axisY->start = glm::vec3(0.0f, -20.0f, 0.0f);
    axisY->end = glm::vec3(0.0f, 20.0f, 0.0f);
    axisY->color = glm::vec4(1.0f, 0.0, 0.0, 1.0);
    std::shared_ptr<GameObject> axisYObject = std::make_shared<GameObject>(axisY);

    std::shared_ptr<LinePrototype> axisZ = std::make_shared<LinePrototype>();
    axisZ->instanced = false;
    axisZ->shaderType = COLOR;
    axisZ->start = glm::vec3(0.0f, 0.0f, -20.0f);
    axisZ->end = glm::vec3(0.0f, 0.0f, 20.0f);
    axisZ->color = glm::vec4(0.0f, 0.0, 1.0, 1.0);
    std::shared_ptr<GameObject> axisZObject = std::make_shared<GameObject>(axisZ);

    scene->addObject(skyBoxObject);

    scene->addObject(axisXObject);
    scene->addObject(axisYObject);
    scene->addObject(axisZObject);
    scene->addObject(gridObject);


    return scene;
}