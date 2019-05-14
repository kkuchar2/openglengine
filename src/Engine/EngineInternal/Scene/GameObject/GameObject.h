#pragma once

#include "GameObjectBase.h"

class GameObject : public GameObjectBase {

    public:

        std::vector<std::shared_ptr<GameObject>> children;

        int rb_idx = -1;

        GameObject(
            const glm::vec3 & position = glm::vec3(0.0f),
            const glm::vec3 & rotation = glm::vec3(0.0f),
            const glm::vec3 & scale = glm::vec3(1.0f)
        );

        virtual void update(const bool & refreshMatrices);
};