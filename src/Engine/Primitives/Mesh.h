#ifndef OPENGL_RENDEROBJECT_H
#define OPENGL_RENDEROBJECT_H

#include <memory>
#include <functional>
#include <map>
#include <thread>

#include "../Base/Component.h"
#include "../TextureLoader.h"
#include "../Shader.h"

#include "../tiny_obj_loader.h"

enum RenderFlag {
    ORTHOGRAPHIC,
    PERSPECTIVE
};


struct Transform {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation =  glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
};

struct FaceInfo {
    int id;
    float angle;
    glm::vec3 normal;
};


typedef std::shared_ptr<Shader>& ShaderPtrRef;
typedef std::function<void(ShaderPtrRef)> ShaderFunc;

class Mesh : public Component {
    public:

        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        std::vector<float> uvs;
        std::vector<float> normals;

        RenderFlag renderFlag = RenderFlag::PERSPECTIVE;
        GLenum mode = GL_TRIANGLES;
        bool disableNormals = false;

        bool dataReady = false;
        bool prepared = false;

        GLuint textureId = 0;

        std::shared_ptr<Shader> shader;

        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint uvbo = 0;
        GLuint nbo = 0;
        GLuint ibo = 0;

        Transform transform;

        ShaderFunc shaderInit = [](std::shared_ptr<Shader> & shader) { };

        void loadTexture(const char * path) {
            textureId = TextureLoader::load(path);
        }

        void prepare() {

            std::cout << "Preparing mesh" << std::endl;

            calculateNormals();

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            // Create index buffer
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            // Create vertex buffer
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);

            // Enable vertex attribute array and set vertex attribute pointers
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

            // Create UV buffer
            glGenBuffers(1, &uvbo);
            glBindBuffer(GL_ARRAY_BUFFER, uvbo);
            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), &uvs[0], GL_DYNAMIC_DRAW);

            // Enable uv attribute array and set uv attribute pointers
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

            // Create normals buffer
            glGenBuffers(1, &nbo);
            glBindBuffer(GL_ARRAY_BUFFER, nbo);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_DYNAMIC_DRAW);

            // Enable normals attribute array and set normals attribute pointers
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindVertexArray(0);

            prepared = true;
        }

        void UpdateVertexBuffer() {
            prepared = false;
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
            prepared = true;
        }

        virtual void Render() {
            Render(mode, static_cast<int>(indices.size()));
        }

        void Render(GLenum mode, int count) {
            glBindVertexArray(vao);
            glDrawElements(mode, count, GL_UNSIGNED_INT, 0);
        }

        void calculateNormals() {
            if (disableNormals)  {
                return;
            }

            // Create map of vertex id to list of face ids (with angles), that share that vertex
            std::map<int, std::vector<FaceInfo>> vertexToFaces;

            for (int vertexId = 0; vertexId < vertices.size() / 3; vertexId++) {

                std::vector<FaceInfo> faces;

                // Iterate over faces and check which one shares current vertex
                for (int j = 0; j < indices.size() / 3; j++) {

                    unsigned int v1 = indices[j * 3];       // index of vector 1 constructing face
                    unsigned int v2 = indices[j * 3 + 1];   // index of vector 2 constructing face
                    unsigned int v3 = indices[j * 3 + 2];   // index of vector 3 constructing face

                    glm::vec3 v_1 = glm::vec3(vertices[v1 * 3], vertices[v1 * 3 + 1], vertices[v1 * 3 + 2]);
                    glm::vec3 v_2 = glm::vec3(vertices[v2 * 3], vertices[v2 * 3 + 1], vertices[v2 * 3 + 2]);
                    glm::vec3 v_3 = glm::vec3(vertices[v3 * 3], vertices[v3 * 3 + 1], vertices[v3 * 3 + 2]);

                    glm::vec3 a;
                    glm::vec3 b;

                    bool hasFace = false;

                    if (v1 == vertexId) {
                        hasFace = true;
                        a = v_2 - v_1;
                        b = v_3 - v_1;
                    } else if (v2 == vertexId) {
                        hasFace = true;
                        a = v_3 - v_2;
                        b = v_1 - v_2;
                    } else if (v3 == vertexId) {
                        hasFace = true;
                        a = v_1 - v_3;
                        b = v_2 - v_3;
                    }

                    if (hasFace) {
                        float dot = glm::dot(a, b);
                        float length_a = glm::length(a);
                        float length_b = glm::length(b);
                        float angle = static_cast<float>(acos(dot / (length_a * length_b)));

                        FaceInfo faceInfo{};

                        faceInfo.id = j;
                        faceInfo.angle = angle;
                        faceInfo.normal = glm::normalize(glm::cross(a, b));

                        faces.emplace_back(faceInfo);
                    }
                }

                vertexToFaces.insert(std::pair<int, std::vector<FaceInfo>>(vertexId, faces));
            }

            for (auto &vertexToFace : vertexToFaces) {

                std::vector<FaceInfo> faceInfos = vertexToFace.second;

                glm::vec3 weightedSum = glm::vec3(0.0, 0.0, 0.0);

                for (auto &faceInfo : faceInfos) {
                    weightedSum += faceInfo.normal * faceInfo.angle;
                }

                weightedSum /= faceInfos.size();

                normals.push_back(weightedSum.x);
                normals.push_back(weightedSum.y);
                normals.push_back(weightedSum.z);
            }
        }

        void loadMesh(const char * path) {

            std::cout << "Started loading: " << path << std::endl;

            tinyobj::attrib_t attrib;

            std::string warning;
            std::string error;

            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;

            bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, path);

            if (!error.empty()) {
                std::cerr << error << std::endl;
            }

            if (!warning.empty()) {
                std::cerr << error << std::endl;
            }

            vertices = attrib.vertices;

            for (const auto &shape : shapes) {
                for (const auto &index : shape.mesh.indices) {
                    indices.push_back((unsigned int) index.vertex_index);
                }
            }

            dataReady = true;

            std::cout << "Finished loading: " << path << std::endl;
        }

        void log() {
            std::cout << "VERTICES:" << std::endl;
            for (int i = 0; i < vertices.size(); i++) {
                std::cout << vertices[i] << " ";

                if ((i + 1) % 3 == 0 && i != 0) {
                    std::cout << std::endl;
                }
            }

            std::cout << std::endl;

            std::cout << "INDICES:" << std::endl;

            for (int i = 0; i < indices.size(); i++) {
                std::cout << indices[i] << " ";

                if (i % 10 == 0 && i != 0) {
                    std::cout << std::endl;
                }
            }
        }
};

#endif //OPENGL_RENDEROBJECT_H
