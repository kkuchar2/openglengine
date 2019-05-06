#pragma once

#include <Engine/Engine.h>
#include <Primitives/Surface.h>

std::shared_ptr<Scene> mainScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(2.2f, 3.0f, 2.0f);

    std::shared_ptr<MeshComponent> lampMeshProto = std::make_shared<MeshComponent>();
    std::shared_ptr<MeshComponent> cubeMeshProto = std::make_shared<MeshComponent>();
    std::shared_ptr<MeshComponent> bunnyMeshProto = std::make_shared<MeshComponent>();
    std::shared_ptr<MeshComponent> suzanneMeshProto = std::make_shared<MeshComponent>();
    std::shared_ptr<MeshComponent> teapotMeshProto = std::make_shared<MeshComponent>();
    std::shared_ptr<MeshComponent> surfaceMeshProto = std::make_shared<MeshComponent>();


    cubeMeshProto->meshType = CUBE;
    cubeMeshProto->shaderType = PHONG;
    cubeMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    surfaceMeshProto->meshType = SURFACE;
    surfaceMeshProto->shaderType = PHONG;
    surfaceMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    bunnyMeshProto->meshType = RESOURCE;
    bunnyMeshProto->path = "../resources/models/bunny.obj";
    bunnyMeshProto->shaderType = PHONG;
    bunnyMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    suzanneMeshProto->meshType = RESOURCE;
    suzanneMeshProto->path = "../resources/models/suzanne.obj";
    suzanneMeshProto->shaderType = PHONG;
    suzanneMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    teapotMeshProto->meshType = RESOURCE;
    teapotMeshProto->path = "../resources/models/teapot.obj";
    teapotMeshProto->shaderType = PHONG;
    teapotMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    lampMeshProto->meshType = RESOURCE;
    lampMeshProto->path = "../resources/models/sphere.obj";
    lampMeshProto->shaderType = AMBIENT;
    lampMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    std::shared_ptr<GameObject> lampMeshObject = std::make_shared<GameObject>();
    lampMeshObject->addComponent(lampMeshProto);

    std::shared_ptr<GameObject> cubeObject = std::make_shared<GameObject>();
    cubeObject->addComponent(cubeMeshProto);

    std::shared_ptr<GameObject> bunnyObject = std::make_shared<GameObject>();
    bunnyObject->addComponent(bunnyMeshProto);

    std::shared_ptr<GameObject> suzanneMeshObject = std::make_shared<GameObject>();
    suzanneMeshObject->addComponent(suzanneMeshProto);

    std::shared_ptr<GameObject> teapotMeshObject = std::make_shared<GameObject>();
    teapotMeshObject->addComponent(teapotMeshProto);

    std::shared_ptr<GameObject> surfaceObject = std::make_shared<GameObject>();
    surfaceObject->addComponent(surfaceMeshProto);

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