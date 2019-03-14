#ifndef OPENGL_TESTSCENE_H
#define OPENGL_TESTSCENE_H

#include "../Engine.h"
#include "../Utils/NormalsGenerator.h"

std::shared_ptr<RenderScene> testScene() {
    std::shared_ptr<RenderScene> scene = std::make_shared<RenderScene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-1.2f, 10.0f, 2.0f);

    auto diffuseShader = std::make_shared<Shader>("../resources/shaders/Diffuse.vert", "../resources/shaders/Diffuse.frag");
    auto colorShader = std::make_shared<Shader>("../resources/shaders/Color.vert", "../resources/shaders/Color.frag");

    std::shared_ptr<Mesh> lampMesh = std::make_shared<Mesh>("../resources/models/sphere.obj");
    lampMesh->shader = colorShader;
    lampMesh->transform.scale = glm::vec3(0.1f);
    lampMesh->transform.position = *lightPos.get();
    lampMesh->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    };

    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    cube->shader = diffuseShader;
    cube->transform.position = glm::vec3(0.0f, 0.5f, 0.0f);
    cube->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    std::shared_ptr<Surface> surface = std::make_shared<Surface>(100, 100);
    surface->shader = diffuseShader;
    surface->transform.position = glm::vec3(0.0f, 1.5f, 0.0f);
    surface->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    auto lampMeshObject = std::make_shared<GameObject>(lampMesh);
    auto cubeObject = std::make_shared<GameObject>(cube);
    auto surfaceObject = std::make_shared<GameObject>(surface);

    scene->addObject(surfaceObject);
    scene->addObject(lampMeshObject);
    scene->addObject(cubeObject);

    //std::shared_ptr<GameObject> normals = NormalsGenerator::generate(surface, colorShader);
    //scene->addObject(normals);

    return scene;
}


#endif //OPENGL_TESTSCENE_H
