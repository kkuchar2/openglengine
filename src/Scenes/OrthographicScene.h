#pragma once

#include <Engine.h>

std::shared_ptr<GameObject> quad(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = size;
    obj->transform.position = glm::vec3(position);
    obj->addComponent(MeshPrototype::of(CUBE, DIFFUSE));

    return obj;
}

std::shared_ptr<GameObject> quad(const glm::vec3 & size, const glm::vec3 & position) {
    return quad(size, position, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
}

std::shared_ptr<UserScene> orthographicScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    scene->projection = PERSPECTIVE;

    // Render 250000 quads

    for (int x = 0; x < 500; x++) {
        for (int y = 0; y < 500; y++) {
            scene->addObject(quad(glm::vec3(0.1f), glm::vec3(0.5f * (x - 250),  5.0f * sin(x) * cos(y), 0.5f * (y - 250))));
        }
    }

    return scene;
}

