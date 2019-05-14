#include "RenderingManager.h"

RenderingManager::RenderingManager() = default;

void RenderingManager::preprocessScenes() {

    ///--------------------------------------------------------------------------------------
    ///Create render infos for each GameObject
    ///--------------------------------------------------------------------------------------

    std::cout << "Children size: " << children.size() << std::endl;

    for (auto & child : children) {
        auto meshComponent = child->getComponent<MeshComponent>();
        if (!meshComponent.get()) continue;

        auto meshRenderer = child->getComponentOrDefault<MeshRenderer>();

        if (meshRenderer->instanced) {
            std::string id = meshRenderer->getShaderTypeStr() + "_" + meshComponent->getMeshIdText();


            if (instancedRenderInfos.count(id) == 0) {
                auto mesh = MeshBuilder::buildMesh(meshComponent);
                auto renderInfo = std::make_shared<RenderInfo>(mesh, child, meshRenderer);

                if (meshRenderer->enableBoundingBox) {
                    addBoundingBox(mesh, child);
                }

                instancedRenderInfos.insert(std::make_pair(id, renderInfo));
            }
            else {
                if (meshRenderer->enableBoundingBox) {
                    addBoundingBox(instancedRenderInfos[id]->mesh, child);
                }
                instancedRenderInfos[id]->addInstance(child, meshRenderer->color);
            }
        }
        else {
            auto mesh = MeshBuilder::buildMesh(meshComponent);
            auto renderInfo = std::make_shared<RenderInfo>(mesh, child, meshRenderer);

            renderInfos.emplace_back(renderInfo);

            if (meshRenderer->enableBoundingBox) {
                addBoundingBox(mesh, child);
            }
        }
    }

    logRenderMap();
}

void RenderingManager::logRenderMap() {
    std::cout << "INSTANCED RENDERING:" << std::endl;

    for (auto  &[id, instancedRenderInfo] : instancedRenderInfos) {
        std::cout << "\t* ID: [" << id << "]: " << instancedRenderInfo->objects.size() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "CLASSIC RENDERING:" << std::endl;
    for (auto const & info : renderInfos) {
        std::cout << "\t* Mesh type: [" << info->mesh->meshId << "]" << std::endl;
    }
}

void RenderingManager::addBoundingBox(const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<GameObjectBase> & parent) {

    auto bboxObj = BoundingBoxGenerator::calculateBoundingBox(mesh, parent);
    auto renderer = bboxObj->getComponent<MeshRenderer>();
    auto bboxMesh = MeshBuilder::buildMesh(bboxObj->getComponent<MeshComponent>());

    if (instancedRenderInfos.count("bbox") == 0) {
        instancedRenderInfos.insert(std::make_pair("bbox", std::make_shared<RenderInfo>(bboxMesh, bboxObj, renderer)));
    }
    else {
        instancedRenderInfos["bbox"]->addInstance(bboxObj, renderer->color);
    }
}

