#pragma once

#include <Engine/Engine.h>
#include <Scene/GameObjectFactory/GameObjectFactory.h>
#include <Engine/EngineInternal/Components/Behaviour/RotatorComponent/Rotator.h>

std::shared_ptr<Scene> instancedScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            for (int z = 10; z < 110; z++) {
                std::shared_ptr<GameObject> cube = GameObjectFactory::cube(glm::vec3(x - 50, z - 50 , y - 50), glm::vec3(0.0f),
                                                                             glm::vec3(0.1f),
                                                                             glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

                cube->addComponent(std::make_shared<Rotator>());
                cube->instanced = true;
                scene->addChild(cube);
            }
        }
    }
    return scene;
}