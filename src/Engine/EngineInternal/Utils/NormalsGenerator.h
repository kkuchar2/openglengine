#pragma once

#include "../Engine.h"

class NormalsGenerator {
    public:
        static std::shared_ptr<GameObject> generate(Transform transform, const std::shared_ptr<Mesh> & mesh, const std::shared_ptr<Shader> & colorShader) {

            std::shared_ptr<GameObject> normalsGroup = std::make_shared<GameObject>();
            std::shared_ptr<Mesh> normalsMesh = std::make_shared<Mesh>();

            for (int i = 0; i < mesh->normals.size(); i += 3) {

                glm::vec3 normal = glm::vec3(mesh->normals[i], mesh->normals[i + 1], mesh->normals[i + 2]);
                glm::vec3 vertex = glm::vec3(mesh->vertices[i], mesh->vertices[i + 1], mesh->vertices[i + 2]);

                glm::vec3 start = transform.scale * glm::vec3(vertex) + transform.position;
                glm::vec3 end = start + glm::normalize(normal) / 5.0f;

                normalsMesh->vertices.push_back(start.x);
                normalsMesh->vertices.push_back(start.y);
                normalsMesh->vertices.push_back(start.z);

                normalsMesh->vertices.push_back(end.x);
                normalsMesh->vertices.push_back(end.y);
                normalsMesh->vertices.push_back(end.z);
            }

            for (unsigned int i = 0; i < normalsMesh->vertices.size() / 3; i++) {
                normalsMesh->indices.push_back(i);
            }

            normalsMesh->disableNormals = true;
            normalsMesh->mode = GL_LINES;
            normalsMesh->shader = colorShader;
            normalsMesh->shaderInit = [](ShaderPtrRef shader) {
                shader->setVec4("color", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
            };

            normalsMesh->prepare();
            normalsGroup->addComponent(mesh);
            return normalsGroup;
        }

};