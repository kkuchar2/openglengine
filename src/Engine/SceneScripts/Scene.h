#ifndef OPENGL_SCENE_H
#define OPENGL_SCENE_H

#include "GameObject.h"
#include "../Camera/PerspectiveCamera.h"

class Scene {
    public:
        std::vector<std::shared_ptr<GameObject>> objectsToRender;

        Scene() = default;

        void addObject(std::shared_ptr<GameObject> & obj) {
            objectsToRender.push_back(obj);
        }

        void renderObj(std::shared_ptr<GameObject> & obj, std::shared_ptr<PerspectiveCamera> & camera) {
            std::vector<std::shared_ptr<Component>> components = obj->components;

            for (auto & componentPtr : components) {

                std::shared_ptr<Mesh> mesh =  std::dynamic_pointer_cast<Mesh>(componentPtr);

                if (!mesh) {
                    continue;
                }

                if (mesh->dataReady && !mesh->prepared) {

                    mesh->prepare();
                }

                if (mesh->prepared) {
                    glBindTexture(GL_TEXTURE_2D, mesh->textureId);
                    camera->Render(mesh);
                    break;
                }
            }
        }

        void render(std::shared_ptr<PerspectiveCamera> & camera) {
            for (auto & i : objectsToRender) {
                renderObj(i, camera);
            }
        }
};

#endif //OPENGL_SCENE_H
