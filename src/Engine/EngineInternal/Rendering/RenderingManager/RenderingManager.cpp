#include "RenderingManager.h"

RenderingManager::RenderingManager() = default;

void RenderingManager::addChild(const std::shared_ptr<GameObject> & child) {
    children.push_back(child);
}

void RenderingManager::preprocessScenes() {

    ///--------------------------------------------------------------------------------------
    ///Create real meshes for each GameObject
    ///--------------------------------------------------------------------------------------

    for (auto & child : children) {
        auto proto = child->meshProto;

        if (!proto.get()) continue;

        proto->updateIds();

        std::string id = proto->shaderMeshTypeId;

        if (child->instanced) {
            if (instancedMeshes.count(id) == 0) {
                auto mesh = MeshBuilder::of(proto, child->projection);
                auto meshInfo = MeshInfo::ptr(mesh, child);

                if (!proto->disableBoundingBox) {
                    BoundingBoxGenerator::calculateBoundingBox(mesh, child);
                    meshInfo->boundingBoxes.emplace_back(child->boundingBox);
                }

                instancedMeshes.insert(std::make_pair(id, meshInfo));
            }
            else {
                if (!proto->disableBoundingBox) {
                    BoundingBoxGenerator::calculateBoundingBox(instancedMeshes[id]->mesh, child);
                    instancedMeshes[id]->boundingBoxes.emplace_back(child->boundingBox);
                }
                instancedMeshes[id]->addInstance(child, proto->color);

            }
        }
        else {
            auto mesh = MeshBuilder::of(proto, child->projection);
            meshes.emplace_back(MeshInfo::ptr(mesh, child));

            if (!proto->disableBoundingBox) {
                BoundingBoxGenerator::calculateBoundingBox(mesh, child);
            }
        }
    }


    ///---------------------------------------------------------------------------------------
    /// Add bounding boxes
    /// --------------------------------------------------------------------------------------

    for (auto & child : children) {

        auto boundingBox = child->boundingBox;

        if (!boundingBox.get()) continue;

        auto proto = boundingBox->meshProto;

        if (instancedMeshes.count("bbox") == 0) {
            auto mesh = MeshBuilder::of(proto, PERSPECTIVE);
            instancedMeshes.insert(std::make_pair("bbox", MeshInfo::ptr(mesh, boundingBox)));
        }
        else {
            instancedMeshes["bbox"]->addInstance(boundingBox, proto->color);
        }
    }

    ///---------------------------------------------------------------------------------------
    /// Init transform of each child
    /// --------------------------------------------------------------------------------------

    for (const auto & child : children) {
        child->init();

        ///---------------------------------------------------------------------------------------
        /// If physics enabled, register bounding box to physics engine
        /// --------------------------------------------------------------------------------------
        if (child->boundingBox.get() && physicsEnabled) {
            child->rb_idx = physicsEngine->addCollisionBox(1.0f, child->boundingBox->transform.position, child->boundingBox->transform.scale);
        }

        child->Update();
    }

    logRenderMap();
}

void RenderingManager::Update(const std::shared_ptr<PerspectiveCamera> & camera) {
    for (const auto & child : children) {

        float distance = glm::distance(camera->getPosition(), child->transform.position);

        if (distance > 20.0f) continue;

        child->Update();

        auto boundingBox = child->boundingBox;

        if (boundingBox.get() && physicsEnabled) {
            std::shared_ptr<Transform> t = physicsEngine->getTransform(child->rb_idx - 1);
            child->transform.position = t->position;
            child->transform.init();
        }
    }
}

void RenderingManager::logRenderMap() {
    std::cout << "INSTANCED RENDERING:" << std::endl;

    for (auto  &[id, instancedMeshInfo] : instancedMeshes) {
        std::cout << "\t* ID: [" << id << "]: " << instancedMeshInfo->objects.size() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "CLASSIC RENDERING:" << std::endl;
    for (auto const & info : meshes) {
        std::cout << "\t* Mesh type: [" << info->mesh->meshType << "]" << std::endl;
    }
}

