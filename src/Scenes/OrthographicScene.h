#pragma once

#include <Engine.h>

#include <Rendering/Primitives/Prototypes/QuadPrototype.h>

std::shared_ptr<GameObject> quad(float sizeX, float sizeY, const glm::vec2 & position, const glm::vec4 & color) {
    std::shared_ptr<QuadPrototype> quadMeshProto = std::make_shared<QuadPrototype>();
    quadMeshProto->shaderType = COLOR;

    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = glm::vec3(sizeX, sizeY, 1.0f);
    obj->transform.position = glm::vec3(position, 0.0f);

    obj->addComponent(quadMeshProto);

    return obj;
}

std::shared_ptr<GameObject> quad(const glm::vec2 & size, const glm::vec2 & position) {
    return quad(size.x, size.y, position, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
}

std::shared_ptr<UserScene> orthographicScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    scene->projection = ORTOGRAPHIC;

    // Render 250000 quads

    for (int x = 0; x < 500; x++) {
        for (int y = 0; y < 500; y++) {
            scene->addObject(quad(glm::vec2(1.0f), glm::vec2(2.0f * x, 2.0f * y)));
        }
    }

    return scene;
}

