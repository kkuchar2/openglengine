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
        auto meshComponent = child->getComponent<MeshComponent>();
        if (!meshComponent.get()) continue;

        auto meshRenderer = child->getComponentOrDefault<MeshRenderer>();
        meshRenderer->projection = child->projection;

        if (child->instanced) {
            std::string id = meshRenderer->getShaderTypeStr() + "_" + meshComponent->getMeshIdText();

            if (instancedMeshes.count(id) == 0) {
                auto mesh = MeshBuilder::buildMesh(meshComponent);
                auto meshInfo = std::make_shared<MeshInfo>(mesh, child, meshRenderer);

                if (meshRenderer->enableBoundingBox) {
                    BoundingBoxGenerator::calculateBoundingBox(mesh, child);
                }

                instancedMeshes.insert(std::make_pair(id, meshInfo));
            }
            else {
                if (meshRenderer->enableBoundingBox) {
                    BoundingBoxGenerator::calculateBoundingBox(instancedMeshes[id]->mesh, child);
                }
                instancedMeshes[id]->addInstance(child, meshRenderer->color);
            }
        }
        else {
            auto mesh = MeshBuilder::buildMesh(meshComponent);
            auto meshInfo = std::make_shared<MeshInfo>(mesh, child, meshRenderer);

            meshes.emplace_back(meshInfo);

            if (meshRenderer->enableBoundingBox) {
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

        auto meshComponent = boundingBox->getComponent<MeshComponent>();

        if (!meshComponent.get()) continue;

        auto meshRenderer = boundingBox->getComponent<MeshRenderer>();

        if (instancedMeshes.count("bbox") == 0) {
            auto mesh = MeshBuilder::buildMesh(meshComponent);
            auto meshInfo =  std::make_shared<MeshInfo>(mesh, boundingBox, meshRenderer);
            instancedMeshes.insert(std::make_pair("bbox", meshInfo));
        }
        else {
            instancedMeshes["bbox"]->addInstance(boundingBox, meshRenderer->color);
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

        child->update();
    }

    logRenderMap();
}

void RenderingManager::Update(const std::shared_ptr<PerspectiveCamera> & camera) {
    for (const auto & child : children) {

        float distance = glm::distance(camera->getPosition(), child->transform.position);

        child->update();

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
        std::cout << "\t* Mesh type: [" << info->mesh->meshId << "]" << std::endl;
    }
}

