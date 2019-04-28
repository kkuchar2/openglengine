#pragma once

#include <Engine.h>
#include <Primitives/Surface.h>
#include <Behaviour/RotatingBehaviour.h>

std::shared_ptr<Scene> mainScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(2.2f, 3.0f, 2.0f);

    std::shared_ptr<MeshPrototype> lampMeshProto = std::make_shared<MeshPrototype>();
    std::shared_ptr<MeshPrototype> cubeMeshProto = std::make_shared<MeshPrototype>();
    std::shared_ptr<MeshPrototype> bunnyMeshProto = std::make_shared<MeshPrototype>();
    std::shared_ptr<MeshPrototype> suzanneMeshProto = std::make_shared<MeshPrototype>();
    std::shared_ptr<MeshPrototype> teapotMeshProto = std::make_shared<MeshPrototype>();
    std::shared_ptr<MeshPrototype> surfaceMeshProto = std::make_shared<MeshPrototype>();

    cubeMeshProto->instanced = true;
    cubeMeshProto->meshType = CUBE;
    cubeMeshProto->shaderType = PHONG;
    cubeMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    surfaceMeshProto->instanced = true;
    surfaceMeshProto->meshType = SURFACE;
    surfaceMeshProto->shaderType = PHONG;
    surfaceMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    bunnyMeshProto->instanced = true;
    bunnyMeshProto->meshType = RESOURCE;
    bunnyMeshProto->path = "../resources/models/bunny.obj";
    bunnyMeshProto->shaderType = PHONG;
    bunnyMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    suzanneMeshProto->instanced = true;
    suzanneMeshProto->meshType = RESOURCE;
    suzanneMeshProto->path = "../resources/models/suzanne.obj";
    suzanneMeshProto->shaderType = PHONG;
    suzanneMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    teapotMeshProto->instanced = true;
    teapotMeshProto->meshType = RESOURCE;
    teapotMeshProto->path = "../resources/models/teapot.obj";
    teapotMeshProto->shaderType = PHONG;
    teapotMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    lampMeshProto->instanced = true;
    lampMeshProto->meshType = RESOURCE;
    lampMeshProto->path = "../resources/models/sphere.obj";
    lampMeshProto->shaderType = AMBIENT;
    lampMeshProto->color = glm::vec4(1.0, 1.0, 1.0f, 1.0f);

    std::shared_ptr<GameObject> lampMeshObject = std::make_shared<GameObject>(lampMeshProto);
    std::shared_ptr<GameObject> cubeObject = std::make_shared<GameObject>(cubeMeshProto);
    std::shared_ptr<GameObject> bunnyObject = std::make_shared<GameObject>(bunnyMeshProto);
    std::shared_ptr<GameObject> suzanneMeshObject = std::make_shared<GameObject>(suzanneMeshProto);
    std::shared_ptr<GameObject> teapotMeshObject = std::make_shared<GameObject>(teapotMeshProto);
    std::shared_ptr<GameObject> surfaceObject = std::make_shared<GameObject>(surfaceMeshProto);

    lampMeshObject->transform.scale = glm::vec3(0.1f);
    lampMeshObject->transform.position = *lightPos.get();

    cubeObject->transform.position = glm::vec3(2.0f, 0.5f, 0.0f);
    cubeObject->addComponent(std::make_shared<RotatingBehaviour>());

    bunnyObject->addComponent(std::make_shared<RotatingBehaviour>());
    bunnyObject->transform.scale = glm::vec3(20.0f);


    suzanneMeshObject->addComponent(std::make_shared<RotatingBehaviour>());
    suzanneMeshObject->transform.position = glm::vec3(0.0f, 7.0f, 0.0f);
    suzanneMeshObject->transform.rotation = glm::vec3(0.0f, 30.0f, -10.0f);

    teapotMeshObject->transform.position = glm::vec3(-3.0f, 1.0f, 0.0f);
    teapotMeshObject->transform.scale = glm::vec3(0.5f);
    teapotMeshObject->addComponent(std::make_shared<RotatingBehaviour>());

    surfaceObject->transform.position = glm::vec3(0.0f, 0.1f, -10.0f);

    //scene->addChild(surfaceObject);
    scene->addChild(lampMeshObject);
    scene->addChild(teapotMeshObject);
    scene->addChild(suzanneMeshObject);
    scene->addChild(bunnyObject);
    scene->addChild(cubeObject);

    return scene;
}