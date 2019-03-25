#pragma once

#include "GameObject.h"
#include "../Camera/PerspectiveCamera.h"

class Scene {
    public:

        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<GameObject>> objectsToRender;

        Scene() = default;

        void addObject(std::shared_ptr<GameObject> & obj) {
            objectsToRender.push_back(obj);
        }

        void prepare() {
            for (auto & o : objectsToRender) {
                for (auto & componentPtr : o->components) {

                    std::shared_ptr<Mesh> mesh =  std::dynamic_pointer_cast<Mesh>(componentPtr);

                    if (mesh) {
                        mesh->prepare();
                    }
                }
            }
        }

        template<typename T, typename std::enable_if<std::is_base_of<Component, BaseCamera>::value>::type* = nullptr>
        void render(std::shared_ptr<T> & camera) {
            for (auto & o : objectsToRender) {
                for (auto & componentPtr : o->components) {

                    std::shared_ptr<Mesh> mesh =  std::dynamic_pointer_cast<Mesh>(componentPtr);

                    if (mesh) {
                        camera->Render(mesh);
                    }
                }
            }
        }
};