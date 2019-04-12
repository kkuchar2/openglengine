#pragma once

#include <Engine.h>
#include <Utils/Objects.h>

std::shared_ptr<UserScene> instancedScene() {
    std::shared_ptr<UserScene> scene = std::make_shared<UserScene>();

    int i = 0;

    scene->addObject(sphere(glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {

            if (i % 2 == 0) {
                scene->addObject(teapot(glm::vec3(0.1f), glm::vec3(x - 10, 0.0f, y - 10), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
            }
            else {
                scene->addObject(bunny(glm::vec3(3.0f), glm::vec3(x - 10, 0.0f, y - 10), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
            }
            i++;
        }
    }

    scene->addObject(surface(glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

    return scene;
}

