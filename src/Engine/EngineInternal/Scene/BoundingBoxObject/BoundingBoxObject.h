#pragma once

#include "../GameObject/GameObject.h"

class BoundingBoxObject : public GameObjectBase {
    public:

        std::shared_ptr<GameObjectBase> parent;

        void update(const bool & refreshMatrices) override;

        virtual void update(const Transform & t, const BoundingBox & bb, const bool & refreshMatrices) override;
};