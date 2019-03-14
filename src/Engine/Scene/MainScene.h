#ifndef OPENGL_MAINSCENE_H
#define OPENGL_MAINSCENE_H

#include "../Engine.h"

std::shared_ptr<RenderScene> mainScene() {
    std::shared_ptr<RenderScene> scene = std::make_shared<RenderScene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(1.2f, 1.0f, 2.0f);

    ShaderPool shaderPool;

    std::shared_ptr<Mesh> lampMesh = std::make_shared<Mesh>("../resources/models/sphere.obj");
    lampMesh->shader = shaderPool.colorShader;
    lampMesh->transform.scale = glm::vec3(0.1f);
    lampMesh->transform.position = *lightPos.get();
    lampMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->shader = shaderPool.diffuseShader;
    cube->transform.position = glm::vec3(2.0f, 0.5f, 0.0f);
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> bunnyMesh = std::make_shared<Mesh>("../resources/models/bunny.obj");
    bunnyMesh->shader = shaderPool.diffuseShader;
    bunnyMesh->transform.scale = glm::vec3(10.0f);
    bunnyMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> suzanneMesh = std::make_shared<Mesh>("../resources/models/suzanne.obj");
    suzanneMesh->shader = shaderPool.diffuseShader;
    suzanneMesh->transform.position = glm::vec3(0.0f, 3.0f, 0.0f);
    suzanneMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Mesh> teapotMesh = std::make_shared<Mesh>("../resources/models/teapot.obj");
    teapotMesh->shader = shaderPool.diffuseShader;
    teapotMesh->transform.position = glm::vec3(-3.0f, 1.0f, 0.0f);
    teapotMesh->transform.scale = glm::vec3(0.5f);
    teapotMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Surface> surface = std::make_shared<Surface>(300, 300);
    surface->shader = shaderPool.diffuseShader;
    surface->transform.position = glm::vec3(0.0f, 0.1f, -10.0f);
    surface->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    auto lampMeshObject = std::make_shared<GameObject>(lampMesh);
    auto cubeObject = std::make_shared<GameObject>(cube);
    auto bunnyObject = std::make_shared<GameObject>(bunnyMesh);
    auto suzanneMeshObject = std::make_shared<GameObject>(suzanneMesh);
    auto teapotMeshObject = std::make_shared<GameObject>(teapotMesh);
    auto surfaceObject = std::make_shared<GameObject>(surface);

    scene->addObject(surfaceObject);
    scene->addObject(lampMeshObject);
    scene->addObject(teapotMeshObject);
    scene->addObject(suzanneMeshObject);
    scene->addObject(bunnyObject);
    scene->addObject(cubeObject);
    scene->addObject(lampMeshObject);

    return scene;
}

#endif //OPENGL_MAINSCENE_H