#pragma once

#include <Engine/Engine.h>
#include <Scene/GameObjectFactory/GameObjectFactory.h>
#include <Engine/EngineInternal/Components/Behaviour/RotatorComponent/Rotator.h>

std::shared_ptr<Scene> instancedScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    srand (static_cast <unsigned> (time(0)));

    for (int x = 0; x < 50; x++) {
        for (int y = 0; y < 50; y++) {
            for (int z = 10; z < 60; z++) {

                float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                std::shared_ptr<GameObject> cube = GameObjectFactory::cube(glm::vec3(x - 25, z - 25 , y - 25), glm::vec3(0.0f),
                                                                             glm::vec3(0.1f),
                                                                             glm::vec4(r, g, b, 1.0f));

                cube->addComponent(std::make_shared<Rotator>());
                cube->instanced = true;
                scene->addChild(cube);
            }
        }
    }
    return scene;
}