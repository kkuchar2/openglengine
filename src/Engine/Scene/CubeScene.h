#ifndef OPENGL_CUBESCENE_H
#define OPENGL_CUBESCENE_H

#include "../Engine.h"
#include "../Utils/NormalsGenerator.h"

std::shared_ptr<RenderScene> cubeScene() {
    std::shared_ptr<RenderScene> scene = std::make_shared<RenderScene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-2.0f, 2.0f, 2.0f);

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
    cube->transform.position = glm::vec3(0.0f, 0.5f, 0.0f);
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    auto lampMeshObject = std::make_shared<GameObject>(lampMesh);
    auto cubeObject = std::make_shared<GameObject>(cube);

    scene->addObject(lampMeshObject);
    scene->addObject(cubeObject);

    std::shared_ptr<GameObject> normals = NormalsGenerator::generate(cube, shaderPool.colorShader);
    scene->addObject(normals);

    return scene;
}

#endif //OPENGL_CUBESCENE_H
