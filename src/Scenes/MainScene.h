#pragma once

#include <Engine.h>
#include <Primitives/Surface.h>

std::shared_ptr<UserScene> mainScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(1.2f, 1.0f, 2.0f);

    std::shared_ptr<Mesh> lampMesh = std::make_shared<Mesh>("../resources/models/sphere.obj");
    lampMesh->shader = ShaderPool::Instance().colorShader;
    lampMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->shader = ShaderPool::Instance().diffuseShader;
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> bunnyMesh = std::make_shared<Mesh>("../resources/models/bunny.obj");
    bunnyMesh->shader = ShaderPool::Instance().diffuseShader;
    bunnyMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> suzanneMesh = std::make_shared<Mesh>("../resources/models/suzanne.obj");
    suzanneMesh->shader = ShaderPool::Instance().diffuseShader;
    suzanneMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> teapotMesh = std::make_shared<Mesh>("../resources/models/teapot.obj");
    teapotMesh->shader = ShaderPool::Instance().diffuseShader;
    teapotMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Surface> surface = std::make_shared<Surface>(300, 300);
    surface->shader = ShaderPool::Instance().diffuseShader;
    surface->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    auto lampMeshObject = std::make_shared<GameObject>(lampMesh);
    lampMeshObject->transform.scale = glm::vec3(0.1f);
    lampMeshObject->transform.position = *lightPos.get();


    auto cubeObject = std::make_shared<GameObject>(cube);
    cubeObject->transform.position = glm::vec3(2.0f, 0.5f, 0.0f);

    auto bunnyObject = std::make_shared<GameObject>(bunnyMesh);
    bunnyObject->transform.scale = glm::vec3(10.0f);

    auto suzanneMeshObject = std::make_shared<GameObject>(suzanneMesh);
    suzanneMeshObject->transform.position = glm::vec3(0.0f, 7.0f, 0.0f);
    suzanneMeshObject->transform.rotation = glm::vec3(0.0f, 30.0f, -10.0f);

    auto teapotMeshObject = std::make_shared<GameObject>(teapotMesh);
    teapotMeshObject->transform.position = glm::vec3(-3.0f, 1.0f, 0.0f);
    teapotMeshObject->transform.scale = glm::vec3(0.5f);

    auto surfaceObject = std::make_shared<GameObject>(surface);
    surfaceObject->transform.position = glm::vec3(0.0f, 0.1f, -10.0f);

    scene->addObject(surfaceObject);
    scene->addObject(lampMeshObject);
    scene->addObject(teapotMeshObject);
    scene->addObject(suzanneMeshObject);
    scene->addObject(bunnyObject);
    scene->addObject(cubeObject);
    scene->addObject(lampMeshObject);

    return scene;
}