#pragma once

#include <Mesh/Primitives/Quad.h>
#include <Mesh/Primitives/LineMeshComponent.h>

#include "Shading/ShaderPool.h"

#include "Scene.h"

std::shared_ptr<Scene> baseEngineScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<MeshComponent> skyboxMesh = std::make_shared<MeshComponent>();
    skyboxMesh->meshType = CUBE;

    std::shared_ptr<MeshRenderer> skyboxMeshRenderer = std::make_shared<MeshRenderer>();
    skyboxMeshRenderer->frustumCulling = false;
    skyboxMeshRenderer->enableBoundingBox = false;
    skyboxMeshRenderer->shaderType = TEXTURE_CUBE;
    skyboxMeshRenderer->paths = {
            "../resources/textures/skybox/right.jpg",
            "../resources/textures/skybox/left.jpg",
            "../resources/textures/skybox/top.jpg",
            "../resources/textures/skybox/bottom.jpg",
            "../resources/textures/skybox/front.jpg",
            "../resources/textures/skybox/back.jpg"
    };

    std::shared_ptr<GameObject> skyBoxObject = std::make_shared<GameObject>();
    skyBoxObject->addComponent(skyboxMesh);
    skyBoxObject->addComponent(skyboxMeshRenderer);
    skyBoxObject->transform.scale = glm::vec3(10000.0f);

    std::shared_ptr<MeshComponent> gridQuad = std::make_shared<MeshComponent>();
    gridQuad->meshType = QUAD;

    std::shared_ptr<MeshRenderer> gridQuadRenderer = std::make_shared<MeshRenderer>();
    gridQuadRenderer->shaderType = GRID;
    gridQuadRenderer->texture = "../resources/textures/texture_white.bmp";
    gridQuadRenderer->enableBoundingBox = true;
    gridQuadRenderer->frustumCulling = false;

    std::shared_ptr<GameObject> gridObject = std::make_shared<GameObject>();
    gridObject->addComponent(gridQuad);
    gridObject->addComponent(gridQuadRenderer);

    gridObject->transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);
    gridObject->transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);

    std::shared_ptr<LineMeshComponent> axisX = std::make_shared<LineMeshComponent>();
    axisX->start = glm::vec3(-20.0f, 0.0f, 0.0f);
    axisX->end = glm::vec3(20.0f, 0.0f, 0.0f);

    std::shared_ptr<MeshRenderer> axisXRenderer = std::make_shared<MeshRenderer>();
    axisXRenderer->shaderType = AMBIENT;
    axisXRenderer->color = glm::vec4(0.0f, 1.0, 0.0, 1.0);
    axisXRenderer->enableBoundingBox = false;
    axisXRenderer->frustumCulling = false;

    std::shared_ptr<GameObject> axisXObject = std::make_shared<GameObject>();
    axisXObject->addComponent(axisX);
    axisXObject->addComponent(axisXRenderer);

    std::shared_ptr<LineMeshComponent> axisY = std::make_shared<LineMeshComponent>();
    axisY->start = glm::vec3(0.0f, -20.0f, 0.0f);
    axisY->end = glm::vec3(0.0f, 20.0f, 0.0f);

    std::shared_ptr<MeshRenderer> axisYRenderer = std::make_shared<MeshRenderer>();
    axisYRenderer->shaderType = AMBIENT;
    axisYRenderer->color = glm::vec4(1.0f, 0.0, 0.0, 1.0);
    axisYRenderer->enableBoundingBox = false;
    axisYRenderer->frustumCulling = false;

    std::shared_ptr<GameObject> axisYObject = std::make_shared<GameObject>();
    axisYObject->addComponent(axisY);
    axisYObject->addComponent(axisYRenderer);

    std::shared_ptr<LineMeshComponent> axisZ = std::make_shared<LineMeshComponent>();
    axisZ->start = glm::vec3(0.0f, 0.0f, -20.0f);
    axisZ->end = glm::vec3(0.0f, 0.0f, 20.0f);

    std::shared_ptr<MeshRenderer> axisZRenderer = std::make_shared<MeshRenderer>();
    axisZRenderer->shaderType = AMBIENT;
    axisZRenderer->color = glm::vec4(0.0f, 0.0, 1.0, 1.0);
    axisZRenderer->enableBoundingBox = false;
    axisZRenderer->frustumCulling = false;

    std::shared_ptr<GameObject> axisZObject = std::make_shared<GameObject>();
    axisZObject->addComponent(axisZ);
    axisZObject->addComponent(axisZRenderer);

    scene->addChild(skyBoxObject);
    scene->addChild(axisXObject);
    scene->addChild(axisYObject);
    scene->addChild(axisZObject);
    scene->addChild(gridObject);

    return scene;
}