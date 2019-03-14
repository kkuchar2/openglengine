#ifndef OPENGL_NORMALSGENERATOR_H
#define OPENGL_NORMALSGENERATOR_H

#include "../Engine.h"

class NormalsGenerator {
    public:
        template<typename T, typename std::enable_if<std::is_base_of<Mesh, T>::value>::type* = nullptr>
        static std::shared_ptr<GameObject> generate(std::shared_ptr<T> & renderObject, std::shared_ptr<Shader> & colorShader) {

            std::shared_ptr<GameObject> normalsGroup = std::make_shared<GameObject>();
            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

            for (int i = 0; i < renderObject->normals.size(); i += 3) {

                glm::vec3 normal = glm::vec3(renderObject->normals[i], renderObject->normals[i + 1], renderObject->normals[i + 2]);
                glm::vec3 vertex = glm::vec3(renderObject->vertices[i], renderObject->vertices[i + 1], renderObject->vertices[i + 2]);

                glm::vec3 start = renderObject->transform.scale * glm::vec3(vertex) + renderObject->transform.position;
                glm::vec3 end = start + glm::normalize(normal) / 5.0f;

                mesh->vertices.push_back(start.x);
                mesh->vertices.push_back(start.y);
                mesh->vertices.push_back(start.z);

                mesh->vertices.push_back(end.x);
                mesh->vertices.push_back(end.y);
                mesh->vertices.push_back(end.z);
            }

            for (unsigned int i = 0; i < mesh->vertices.size() / 3; i++) {
                mesh->indices.push_back(i);
            }

            mesh->disableNormals = true;
            mesh->mode = GL_LINES;
            mesh->shader = colorShader;
            mesh->shaderInit = [](ShaderPtrRef shader) {
                shader->setVec4("color", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
            };

            mesh->prepare();
            normalsGroup->addComponent(mesh);
            return normalsGroup;
        }

};

#endif //OPENGL_NORMALSGENERATOR_H
