#pragma once

#include "../Engine.h"
#include "../Utils/CharacterTextureGenerator.h"

std::shared_ptr<UserScene> orthographicScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    scene->projection = ORTOGRAPHIC;

    std::shared_ptr<glm::vec3> lightPos = std::make_shared<glm::vec3>(-1.2f, 10.0f, 2.0f);

    CharacterTextureGenerator gen;
    gen.loadFont("../resources/fonts/FreeSans.ttf");
    gen.setFontSize(48);
    gen.init();

    std::shared_ptr<CharacterMesh> c = std::make_shared<CharacterMesh>('B', gen.Characters);
    c->shader = ShaderPool::Instance().characterShader;
    c->transform.scale = glm::vec3(50.0f, 50.0f, 1.0f);
    c->transform.position = glm::vec3(50.0f, 50.0f, 0.0f);
    c->shaderInit = [lightPos](ShaderPtrRef shader) {
        shader->setVec4("color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->setVec3("lightPos", *lightPos.get());
    };

    auto characterObject = std::make_shared<GameObject>(c);
    scene->addObject(characterObject);

    return scene;
}