#ifndef OPENGL_CUBE_H
#define OPENGL_CUBE_H


#include <deps/linmath.h>
#include <map>

struct FaceInfo {
    int id;
    float angle;
    glm::vec3 normal;
};

class Cube : public RenderObject {
    public:
        float vertices[24] = {
                // Front
                -0.5f, -0.5f, -0.5f, // 0 - bottom lefts
                -0.5f, 0.5f, -0.5f, // 1 - top left
                0.5f, 0.5, -0.5f, // 2 - top right
                0.5, -0.5f, -0.5f, // 3 - bottom right

                // Back

                -0.5f, -0.5f, 0.5, // 4 - bottom left
                -0.5f, 0.5f, 0.5, // 5 - top left
                0.5f, 0.5, 0.5, // 6 - top right
                0.5, -0.5f, 0.5, // 7 - bottom right
        };

        unsigned int indices[36] = {
                // front
                0, 1, 2,
                2, 3, 0,
                // right
                1, 5, 6,
                6, 2, 1,
                // back
                7, 6, 5,
                5, 4, 7,
                // left
                4, 0, 3,
                3, 7, 4,
                // bottom
                4, 5, 1,
                1, 0, 4,
                // top
                3, 2, 6,
                6, 7, 3
        };

        float normals[24]; // for each vertex

        float uvs[48]{
                0.0f, 0.0f, // bottom left
                0.0f, 1.0f, // top left
                1.0f, 1.0f, // top right
                1.0f, 0.0f,  // bottom right

                0.0f, 0.0f, // bottom left
                0.0f, 1.0f, // top left
                1.0f, 1.0f, // top right
                1.0f, 0.0f,  // bottom right

                0.0f, 0.0f, // bottom left
                0.0f, 1.0f, // top left
                1.0f, 1.0f, // top right
                1.0f, 0.0f,  // bottom right

                0.0f, 0.0f, // bottom left
                0.0f, 1.0f, // top left
                1.0f, 1.0f, // top right
                1.0f, 0.0f,  // bottom right

                0.0f, 0.0f, // bottom left
                0.0f, 1.0f, // top left
                1.0f, 1.0f, // top right
                1.0f, 0.0f,  // bottom right

                0.0f, 0.0f, // bottom left
                0.0f, 1.0f, // top left
                1.0f, 1.0f, // top right
                1.0f, 0.0f  // bottom right
        };

        explicit Cube() : RenderObject() {

            // Create map of vertex id to list of face ids (with angles), that share that vertex
            std::map<int, std::vector<FaceInfo>> vertexToFaces;

            for (int vertexId = 0; vertexId < 8; vertexId++) {

                //std::cout << "-> Vertex ID: " << vertexId << std::endl;

                std::vector<FaceInfo> faces;

                // Iterate over faces and check which one shares current vertex
                for (int j = 0; j < 12; j++) {

                    //std::cout << "Calculating for face: " << j << std::endl;

                    unsigned int v1 = indices[j * 3];       // index of vector 1 constructing face
                    unsigned int v2 = indices[j * 3 + 1];   // index of vector 2 constructing face
                    unsigned int v3 = indices[j * 3 + 2];   // index of vector 3 constructing face

                    glm::vec3 v_1 = glm::vec3(vertices[v1 * 3], vertices[v1 * 3 + 1], vertices[v1 * 3 + 2]);
                    glm::vec3 v_2 = glm::vec3(vertices[v2 * 3], vertices[v2 * 3 + 1], vertices[v2 * 3 + 2]);
                    glm::vec3 v_3 = glm::vec3(vertices[v3 * 3], vertices[v3 * 3 + 1], vertices[v3 * 3 + 2]);

                    //std::cout << "P0: " << v_1 << std::endl;
                    //std::cout << "P1: " << v_2 << std::endl;
                    //std::cout << "P2: " << v_3 << std::endl;

                    glm::vec3 a;
                    glm::vec3 b;

                    bool hasFace = false;

                    if (v1 == vertexId) {
                        hasFace = true;
                        a = v_2 - v_1;
                        b = v_3 - v_1;
                    }
                    else if (v2 == vertexId) {
                        hasFace = true;
                        a = v_3 - v_2;
                        b = v_1 - v_2;
                    }
                    else if (v3 == vertexId) {
                        hasFace = true;
                        a = v_1 - v_3;
                        b = v_2 - v_3;
                    }

                    if (hasFace) {
                        //std::cout << "a: " << a << " b: " << b << std::endl;

                        float dot = glm::dot(a, b);
                        float length_a = glm::length(a);
                        float length_b = glm::length(b);
                        float angle = acos(dot / (length_a * length_b));

                        //std::cout << "Dot: " << dot << std::endl;
                        //std::cout << "length_a: " << length_a << std::endl;
                        //std::cout << "length_b: " << length_b << std::endl;
                        //std::cout << "Angle: " << angle << std::endl;

                        FaceInfo faceInfo{};

                        faceInfo.id =  j;
                        faceInfo.angle = angle;
                        faceInfo.normal = glm::normalize(glm::cross(a, b));

                        faces.emplace_back(faceInfo);
                    }
                }

                vertexToFaces.insert(std::pair<int, std::vector<FaceInfo>>(vertexId, faces));
            }

            for (auto & vertexToFace : vertexToFaces) {

                int vertexId = vertexToFace.first;

                //std::cout << "VERTEX: " << vertexId << std::endl;

                std::vector<FaceInfo> faceInfos = vertexToFace.second;

                glm::vec3 weightedSum = glm::vec3(0.0, 0.0, 0.0);

                for (auto & faceInfo : faceInfos) {
                    //std::cout << "Face id: " << faceInfo.id << " normal: " << faceInfo.normal << std::endl;
                    weightedSum += faceInfo.normal * faceInfo.angle;
                }

                weightedSum /= faceInfos.size();

                //std::cout << "V[" << vertexId << "]: " << "Weighted sum: " << weightedSum << std::endl;


                normals[vertexId * 3] = weightedSum.x;
                normals[vertexId * 3 + 1] = weightedSum.y;
                normals[vertexId * 3 + 2] = weightedSum.z;
            }
            prepare(vertices, indices, uvs, normals, sizeof(vertices), sizeof(indices), sizeof(uvs), sizeof(normals));
        }

        void Render() override {
            RenderObject::Render(GL_TRIANGLES, 36);
        }
};


#endif //OPENGL_CUBE_H