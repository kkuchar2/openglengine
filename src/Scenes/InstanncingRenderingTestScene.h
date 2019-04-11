#pragma once

#include <Engine.h>

std::shared_ptr<GameObject> sphere(const glm::vec3 & size, const glm::vec3 & position, const glm::vec4 & color) {
    std::shared_ptr<GameObject> obj = GameObject::create();
    obj->transform.scale = size;
    obj->transform.position = glm::vec3(position);
    obj->addComponent(MeshPrototype::of("../resources/models/sphere.obj", DIFFUSE, color));
    return obj;
}

std::shared_ptr<UserScene> orthographicScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    for (int x = 0; x < 200; x++) {
        for (int y = 0; y < 200; y++) {
            scene->addObject(
                sphere(
                    glm::vec3(0.1f),
                    glm::vec3(0.5f * (x - 100),  5.0f * sin(x) * cos(y), 0.5f * (y - 100)),
                    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
                )
            );
        }
    }

    return scene;
}

