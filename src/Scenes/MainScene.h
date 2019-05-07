#pragma once

#include <Engine/Engine.h>
#include <Mesh/Primitives/Surface.h>

std::shared_ptr<Scene> mainScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    auto lightPos = std::make_shared<glm::vec3>(2.2f, 3.0f, 2.0f);

    auto lampMesh = std::make_shared<MeshComponent>();
    auto lampMeshRenderer = std::make_shared<MeshRenderer>();

    auto cubeMesh= std::make_shared<MeshComponent>();
    auto cubeMeshRenderer = std::make_shared<MeshRenderer>();

    auto bunnyMesh = std::make_shared<MeshComponent>();
    auto bunnyMeshRenderer = std::make_shared<MeshRenderer>();

    auto suzanneMesh = std::make_shared<MeshComponent>();
    auto suzanneMeshRenderer = std::make_shared<MeshRenderer>();

    auto teapotMesh = std::make_shared<MeshComponent>();
    auto teapotMeshRenderer = std::make_shared<MeshRenderer>();

    auto coneMesh = std::make_shared<MeshComponent>();
    auto coneMeshRenderer = std::make_shared<MeshRenderer>();

    auto surfaceMesh = std::make_shared<MeshComponent>();
    auto surfaceMeshRenderer = std::make_shared<MeshRenderer>();

    cubeMesh->meshType = CUBE;
    cubeMeshRenderer->shaderType = PHONG;
    cubeMeshRenderer->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    surfaceMesh->meshType = SURFACE;
    surfaceMeshRenderer->shaderType = PHONG;
    surfaceMeshRenderer->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    bunnyMesh->meshType = RESOURCE;
    bunnyMesh->path = "../resources/models/bunny.obj";
    bunnyMeshRenderer->shaderType = PHONG;
    bunnyMeshRenderer->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    suzanneMesh->meshType = RESOURCE;
    suzanneMesh->path = "../resources/models/suzanne.obj";
    suzanneMeshRenderer->shaderType = PHONG;
    suzanneMeshRenderer->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    teapotMesh->meshType = RESOURCE;
    teapotMesh->path = "../resources/models/teapot.obj";
    teapotMeshRenderer->shaderType = PHONG;
    teapotMeshRenderer->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    lampMesh->meshType = RESOURCE;
    lampMesh->path = "../resources/models/sphere.obj";
    lampMeshRenderer->shaderType = AMBIENT;
    lampMeshRenderer->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    auto lampMeshObject = std::make_shared<GameObject>();
    lampMeshObject->addComponent(lampMesh);
    lampMeshObject->addComponent(lampMeshRenderer);

    auto cubeObject = std::make_shared<GameObject>();
    cubeObject->addComponent(cubeMesh);
    cubeObject->addComponent(cubeMeshRenderer);

    auto bunnyObject = std::make_shared<GameObject>();
    bunnyObject->addComponent(bunnyMesh);
    bunnyObject->addComponent(bunnyMeshRenderer);

    auto suzanneMeshObject = std::make_shared<GameObject>();
    suzanneMeshObject->addComponent(suzanneMesh);
    suzanneMeshObject->addComponent(suzanneMeshRenderer);

    auto teapotMeshObject = std::make_shared<GameObject>();
    teapotMeshObject->addComponent(teapotMesh);
    teapotMeshObject->addComponent(teapotMeshRenderer);

    auto surfaceObject = std::make_shared<GameObject>();
    surfaceObject->addComponent(surfaceMesh);
    surfaceObject->addComponent(surfaceMeshRenderer);

    lampMeshObject->transform.scale = glm::vec3(0.1f);
    lampMeshObject->transform.position = *lightPos.get();
    lampMeshObject->instanced = true;

    cubeObject->transform.position = glm::vec3(2.0f, 0.5f, 0.0f);
    cubeObject->instanced = true;

    bunnyObject->transform.scale = glm::vec3(20.0f);
    bunnyObject->instanced = true;

    suzanneMeshObject->transform.position = glm::vec3(0.0f, 7.0f, 0.0f);
    suzanneMeshObject->transform.rotation = glm::vec3(0.0f, 30.0f, -10.0f);
    suzanneMeshObject->instanced = true;

    teapotMeshObject->transform.position = glm::vec3(-3.0f, 1.0f, 0.0f);
    teapotMeshObject->transform.scale = glm::vec3(0.5f);
    teapotMeshObject->instanced = true;

    surfaceObject->transform.position = glm::vec3(0.0f, 0.1f, -10.0f);

    //scene->addChild(surfaceObject);
    scene->addChild(lampMeshObject);
    scene->addChild(teapotMeshObject);
    scene->addChild(suzanneMeshObject);
    scene->addChild(bunnyObject);
    scene->addChild(cubeObject);

    return scene;
}