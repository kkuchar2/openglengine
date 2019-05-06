#pragma once

#include <Scene/GameObject/GameObject.h>
#include <Engine/EngineInternal/Components/MeshComponent/SurfaceMeshComponent.h>

class GameObjectFactory {

    public:
        static std::shared_ptr<GameObject> point(const glm::vec3 & pos, const glm::vec4 & color);

        static std::shared_ptr<GameObject> quad(
                const glm::vec3 & pos = glm::vec3(0.0f),
                const glm::vec3 & rot = glm::vec3(0.0f),
                const glm::vec3 & scale = glm::vec3(1.0f),
                const glm::vec4 & color = glm::vec4(1.0f));

        static std::shared_ptr<GameObject> cube(
                const glm::vec3 & pos = glm::vec3(0.0f),
                const glm::vec3 & rot = glm::vec3(0.0f),
                const glm::vec3 & scale = glm::vec3(1.0f),
                const glm::vec4 & color = glm::vec4(1.0f));

        static std::shared_ptr<GameObject> model(
                const char * path,
                const glm::vec3 & pos = glm::vec3(0.0f),
                const glm::vec3 & rot = glm::vec3(0.0f),
                const glm::vec3 & scale = glm::vec3(1.0f),
                const glm::vec4 & color = glm::vec4(1.0f));

        static std::shared_ptr<GameObject> sphere(
                const glm::vec3 & pos = glm::vec3(0.0f),
                const glm::vec3 & rot = glm::vec3(0.0f),
                const glm::vec3 & scale = glm::vec3(1.0f),
                const glm::vec4 & color = glm::vec4(1.0f));

        static std::shared_ptr<GameObject> bunny(
                const glm::vec3 & pos = glm::vec3(0.0f),
                const glm::vec3 & rot = glm::vec3(0.0f),
                const glm::vec3 & scale = glm::vec3(1.0f),
                const glm::vec4 & color = glm::vec4(1.0f));

        static std::shared_ptr<GameObject> suzanne(
                const glm::vec3 & pos = glm::vec3(0.0f),
                const glm::vec3 & rot = glm::vec3(0.0f),
                const glm::vec3 & scale = glm::vec3(1.0f),
                const glm::vec4 & color = glm::vec4(1.0f));

        static std::shared_ptr<GameObject> teapot(
                const glm::vec3 & pos = glm::vec3(0.0f),
                const glm::vec3 & rot = glm::vec3(0.0f),
                const glm::vec3 & scale = glm::vec3(1.0f),
                const glm::vec4 & color = glm::vec4(1.0f));

        static std::shared_ptr<GameObject> surface(
                const glm::vec3 & pos = glm::vec3(0.0f),
                const glm::vec3 & rot = glm::vec3(0.0f),
                const glm::vec3 & scale = glm::vec3(1.0f),
                const glm::vec4 & color = glm::vec4(1.0f));
};