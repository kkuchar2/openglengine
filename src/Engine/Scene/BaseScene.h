#ifndef OPENGL_BASESCENE_H
#define OPENGL_BASESCENE_H

#include "../Engine.h"
#include "../Rendering/Shading/ShaderPool.h"

std::shared_ptr<RenderScene> baseScene() {
    std::shared_ptr<RenderScene> scene = std::make_shared<RenderScene>();

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-1.2f, 1.0f, 2.0f);

    ShaderPool shaderPool;

    std::shared_ptr<Quad> gridQuad = std::make_shared<Quad>();
    gridQuad->shader = shaderPool.gridShader;
    gridQuad->transform.scale = glm::vec3(100.0f, 100.0f, 100.0f);
    gridQuad->transform.rotation = glm::vec3(glm::radians(90.0), 0.0f, 0.0f);
    gridQuad->loadTexture("../resources/textures/texture_white.bmp");

    std::shared_ptr<Line> axisX = std::make_shared<Line>();
    axisX->shader = shaderPool.colorShader;
    axisX->setCoords(glm::vec3(-20.0f, 0.0f, 0.0f), glm::vec3(20.0f, 0.0f, 0.0f));
    axisX->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 1.0, 0.0, 1.0));
    };

    std::shared_ptr<Line> axisY = std::make_shared<Line>();
    axisY->shader = shaderPool.colorShader;
    axisY->setCoords(glm::vec3(0.0f, -20.0f, 0.0f), glm::vec3(0.0f, 20.0f, 0.0f));
    axisY->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 0.0, 0.0, 1.0));
    };

    std::shared_ptr<Line> axisZ = std::make_shared<Line>();
    axisZ->shader = shaderPool.colorShader;
    axisZ->setCoords(glm::vec3(0.0f, 0.0f, -20.0f), glm::vec3(0.0f, 0.0f, 20.0f));
    axisZ->shaderInit = [](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(0.0f, 0.0, 1.0, 1.0));
    };

    auto gridObject = std::make_shared<GameObject>(gridQuad);
    auto axisXObject = std::make_shared<GameObject>(axisX);
    auto axisYObject = std::make_shared<GameObject>(axisY);
    auto axisZObject = std::make_shared<GameObject>(axisZ);

    scene->addObject(axisXObject);
    scene->addObject(axisYObject);
    scene->addObject(axisZObject);
    scene->addObject(gridObject);
    return scene;
}

#endif //OPENGL_BASESCENE_H