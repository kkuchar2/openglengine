#pragma once

#include <Engine/Engine.h>
#include <Scene/GameObjectFactory/GameObjectFactory.h>
#include <Engine/EngineInternal/Components/Behaviour/RotatorComponent/Rotator.h>

std::shared_ptr<Scene> instancedScene() {
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    srand (static_cast <unsigned> (time(0)));

    for (int x = 0; x < 40; x++) {
        for (int y = 0; y < 40; y++) {
            for (int z = 0; z < 40; z++) {

                float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

                std::shared_ptr<GameObject> cube = GameObjectFactory::cube(
                        glm::vec3(r * 40.0f - 20.0f, g * 40.0f - 20.0f, b * 40.0f - 20.0f), glm::vec3(r, g, b),
                        glm::vec3(0.1f),
                        glm::vec4(r, g, b, 1.0f)
                );

                auto rigidbody = std::make_shared<Rigidbody>();
                rigidbody->mass = 1.0f;
                rigidbody->restitution = 0.2f;

                cube->addComponent(rigidbody);
                cube->addComponent(std::make_shared<Rotator>());

                scene->addChild(cube);
            }
        }
    }
    return scene;
}