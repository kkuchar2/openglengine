#pragma once

#include "../Engine.h"

std::shared_ptr<GameObject> quad(float sizeX, float sizeY, const glm::vec2 & position, const glm::vec4 & color) {
    std::shared_ptr<Quad> quadMesh = std::make_shared<Quad>();
    quadMesh->shader = ShaderPool::Instance().colorShader;
    quadMesh->disableNormals = true;
    quadMesh->shaderInit = [color](ShaderPtrRef shader) {
        shader->setVec4("color", color);
    };

    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = glm::vec3(sizeX, sizeY, 1.0f);
    obj->transform.position = glm::vec3(position, 0.0f);

    obj->addComponent(quadMesh);

    obj->drawBoundingBox = false;

    return obj;
}

std::shared_ptr<GameObject> quad(const glm::vec2 & size, const glm::vec2 & position) {
    return quad(size.x, size.y, position, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
}

std::shared_ptr<UserScene> orthographicScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    scene->projection = ORTOGRAPHIC;

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            scene->addObject(quad(glm::vec2(3.0f), glm::vec2(10.0f * x, 10.0f * y)));
        }
    }

    return scene;
}

