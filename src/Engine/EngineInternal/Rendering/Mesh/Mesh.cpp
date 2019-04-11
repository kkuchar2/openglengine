#include "Mesh/Mesh.h"

Mesh::Mesh(const char * path) : Component::Component() {
    loadMesh(path);
}

Mesh::Mesh() : Component::Component() {}

void Mesh::prepare() {
    std::cout << "Preparing mesh" << std::endl;

    if (prepared) return;

    if (!disableNormals) {
        calculateNormals();
    }

    CreateVertexAttributeObject();
    CreateIndexBuffer();
    CreateVertexBuffer();
    CreateUVBuffer();
    CreateNormalsBuffer();

    if (isInstanced) {
        CreatePositionBuffer();
    }

    glBindVertexArray(0);

    prepared = true;
}

void Mesh::CreateVertexAttributeObject() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Mesh::CreateIndexBuffer() {
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Mesh::CreateVertexBuffer() {
    GLbitfield mapFlags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
    GLbitfield createFlags = mapFlags | GL_DYNAMIC_STORAGE_BIT;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferStorage(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), nullptr, createFlags);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    pVertexPosBufferData = (float *) glMapBufferRange(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), mapFlags);
    copyVertifcesToBuffer();
}

void Mesh::CreateUVBuffer() {
    if (uvs.empty()) return;
    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::CreateNormalsBuffer() {
    if (normals.empty()) return;
    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

/**
 *  When you send the glm::mat4 down the buffer, even though its marked as a single attribute in the vertex shader,
 *  it actually needs 4 attributes because you can only send a max size of 4 in the glVertexAttribPointer call
 *
 *  https://www.reddit.com/r/opengl/comments/6cejtb/why_is_the_stride_in_glvertexattribpointer_for_a/
 *  https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
 *   https://stackoverflow.com/questions/17355051/using-a-matrix-as-vertex-attribute-in-opengl3-core-profile
 */
void Mesh::CreatePositionBuffer() {
    if (modelMatrices.empty()) return;

    glGenBuffers(1, &posvbo);
    glBindBuffer(GL_ARRAY_BUFFER, posvbo);
    glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), modelMatrices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(0));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 8));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 12));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
}

void Mesh::copyVertifcesToBuffer() {
    for (int i = 0; i < vertices.size(); i += 3) {
        pVertexPosBufferData[i] = vertices[i];
        pVertexPosBufferData[i + 1] = vertices[i + 1];
        pVertexPosBufferData[i + 2] = vertices[i + 2];
    }
}

void Mesh::Render(int instancesCount) {
    Render(mode, static_cast<int>(indices.size()), instancesCount);
}

void Mesh::Render(GLenum renderMode, int indicesCount, int instancesCount) {
    glBindVertexArray(vao);
    glDrawElementsInstanced(renderMode, indicesCount, GL_UNSIGNED_INT, (void *) 0, instancesCount);
}

void Mesh::loadTexture(const char * path) {
    textureId = TextureLoader::load(path);
}

void Mesh::calculateNormals() {
    std::map<unsigned int, std::vector<TriangleInfo>> vertexToTriangles;

    std::vector<TriangleInfo> triangles;

    for (unsigned int vertexId = 0; vertexId < vertices.size() / 3; vertexId++) {
        vertexToTriangles.insert(std::pair<int, std::vector<TriangleInfo>>(vertexId, triangles));
    }

    for (unsigned int j = 0; j < indices.size() / 3; j++) {
        unsigned int v1 = indices[j * 3];
        unsigned int v2 = indices[j * 3 + 1];
        unsigned int v3 = indices[j * 3 + 2];

        glm::vec3 v_1 = glm::vec3(vertices[v1 * 3], vertices[v1 * 3 + 1], vertices[v1 * 3 + 2]);
        glm::vec3 v_2 = glm::vec3(vertices[v2 * 3], vertices[v2 * 3 + 1], vertices[v2 * 3 + 2]);
        glm::vec3 v_3 = glm::vec3(vertices[v3 * 3], vertices[v3 * 3 + 1], vertices[v3 * 3 + 2]);

        glm::vec3 a = v_2 - v_1;
        glm::vec3 b = v_3 - v_1;

        TriangleInfo info {};
        info.angle = std::acos(glm::dot(a, b) / (glm::length(a) * glm::length(b)));
        info.normal = glm::normalize(glm::cross(a, b));

        vertexToTriangles.at(v1).emplace_back(info);
        vertexToTriangles.at(v2).emplace_back(info);
        vertexToTriangles.at(v3).emplace_back(info);
    }

    for (auto & pair : vertexToTriangles) {

        std::vector<TriangleInfo> triangleInfos = pair.second;

        glm::vec3 weightedSum = glm::vec3(0.0, 0.0, 0.0);

        for (auto & info : triangleInfos) {
            weightedSum += info.normal * info.angle;
        }

        weightedSum /= triangleInfos.size();

        normals.insert(normals.end(), { weightedSum.x, weightedSum.y, weightedSum.z });
    }
}

void Mesh::loadMesh(const char * path) {
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

    for (const auto & shape : shapes) {
        for (const auto & index : shape.mesh.indices) {
            indices.push_back((unsigned int) index.vertex_index);
        }
    }
}

std::shared_ptr<Mesh> Mesh::create(const char * path) {
    return std::make_shared<Mesh>(path);
}