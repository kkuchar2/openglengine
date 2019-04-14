#pragma once

#include "../Engine.h"
#include "Shading/ShaderPool.h"

#include <Primitives/Quad.h>


#include <Utils/Objects.h>
#include <Rendering/Primitives/LinePrototype.h>

std::shared_ptr<GameObject> cylinder(const glm::vec3 & pos, const glm::vec3 scale, const glm::vec3 rot) {
    std::shared_ptr<MeshPrototype> cylinderMeshProto = std::make_shared<MeshPrototype>();
    cylinderMeshProto->instanced = false;
    cylinderMeshProto->meshType = RESOURCE;
    cylinderMeshProto->path = "../resources/models/cylinder.obj";
    cylinderMeshProto->shaderType = DIFFUSE;
    cylinderMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(cylinderMeshProto);
    obj->transform.position = pos;
    obj->transform.scale = scale;
    obj->transform.rotation = rot;

    return obj;
}

std::shared_ptr<UserScene> baseScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

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

    scene->addObject(axisXObject);
    scene->addObject(axisYObject);
    scene->addObject(axisZObject);
    scene->addObject(gridObject);

    scene->addObject(cylinder(glm::vec3(0.0, 5.0, 10.0), glm::vec3(1.0f), glm::vec3(0.0f)));

    return scene;
}