#pragma once

#include <Engine.h>
#include <Utils/Objects.h>

std::shared_ptr<UserScene> instancedScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    int i = 0;

    for (int x = 0; x < 50; x++) {
        for (int y = 0; y < 50; y++) {
            for (int z = 0; z < 50; z++) {
                scene->addObject(sphere(glm::vec3(0.1f), glm::vec3(x - 25, y - 25, z - 25), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
                i++;
            }
        }
    }

    return scene;
}

