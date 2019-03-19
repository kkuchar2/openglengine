#ifndef OPENGL_SCENE_H
#define OPENGL_SCENE_H

#include "GameObject.h"
#include "Camera/BaseCamera.h"
#include "Mesh.h"

class UserScene {
    public:

        Projection projection = PERSPECTIVE;

        std::vector<std::shared_ptr<GameObject>> objectsToRender;

        UserScene() = default;

        void addObject(std::shared_ptr<GameObject> & obj) {
            objectsToRender.push_back(obj);
        }
};

#endif //OPENGL_SCENE_H
