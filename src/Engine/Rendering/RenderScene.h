#ifndef OPENGL_SCENE_H
#define OPENGL_SCENE_H

#include "GameObject.h"
#include "Camera/BaseCamera.h"
#include "Mesh.h"

class RenderScene {
    public:

        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<GameObject>> objectsToRender;

        RenderScene() = default;

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

        template<typename T, typename std::enable_if<std::is_base_of<MessageListener, BaseCamera>::value>::type* = nullptr>
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

#endif //OPENGL_SCENE_H
