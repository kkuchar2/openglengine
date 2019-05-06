#include "Mesh/Mesh.h"

#include <Utils/NormalsGenerator/NormalsGenerator.h>

Mesh::Mesh(const std::string & path) {
    loadFromResource(path);
}

Mesh::Mesh() {}

void Mesh::prepare() {
    if (prepared) {
        std::cout << "Mesh already prepared" << std::endl;
        return;
    }

    if (!disableNormals) {
        NormalsGenerator::generate(this);
    }

    CreateVertexAttributeObject();
    CreateIndexBuffer();
    CreateVertexBuffer();
    CreateUVBuffer();
    CreateNormalsBuffer();
    CreateModelMatricesBuffer();
    CreateColorBuffer();

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
    if (vertices.empty()) {
        std::cerr << "ERROR: Vertices are empty" << std::endl;
        return;
    }
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::CreateUVBuffer() {
    if (uvs.empty()) {
        std::cerr << "ERROR: UV's are empty" << std::endl;
        return;
    }

    glGenBuffers(1, &uvbo);
    glBindBuffer(GL_ARRAY_BUFFER, uvbo);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::CreateNormalsBuffer() {
    if (normals.empty()) {
        std::cerr << "ERROR: Normals are empty" << std::endl;
        return;
    }

    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::CreateModelMatricesBuffer() {
    if (modelMatrices.empty())  {
        std::cerr << "ERROR: Model matrices are empty" << std::endl;
        return;
    }

    glGenBuffers(1, &model_matrices_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, model_matrices_vbo);
    glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4x4), nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (void *) nullptr);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (void *) (sizeof(float) * 4));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (void *) (sizeof(float) * 8));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (void *) (sizeof(float) * 12));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
}

void Mesh::CreateColorBuffer() {
    if (colorVectors.empty()) {
        std::cerr << "ERROR: Color vectors are empty" << std::endl;
        return;
    }

    glGenBuffers(1, &color_vectors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vectors_vbo);
    glBufferData(GL_ARRAY_BUFFER, colorVectors.size() * sizeof(glm::vec4), nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void *) nullptr);

    glVertexAttribDivisor(7, 1);
}

void Mesh::render(GLenum renderMode, int indicesCount) {
    glBindTexture(cubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, textureId);
    glBindVertexArray(vao);
    glDrawElements(renderMode, indicesCount, GL_UNSIGNED_INT, (void *) nullptr);
}

void Mesh::renderInstanced(GLenum renderMode, int indicesCount, int instancesCount) {
    glBindTexture(cubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, textureId);
    glBindVertexArray(vao);
    glDrawElementsInstanced(renderMode, indicesCount, GL_UNSIGNED_INT, (void *) nullptr, instancesCount);
}

void Mesh::render() {
    render(mode, static_cast<int>(indices.size()));
}

void Mesh::renderInstanced(int instancesCount) {
    renderInstanced(mode, static_cast<int>(indices.size()), instancesCount);
}

void Mesh::UpdateModelMatrices() {
    if (modelMatrices.empty()) {
        std::cerr << "ERROR: model matrices are empty" << std::endl;
        return;
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, model_matrices_vbo);
    glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4x4), modelMatrices.data(), GL_STREAM_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (void *) nullptr);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (void *) (sizeof(float) * 4));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (void *) (sizeof(float) * 8));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4x4), (void *) (sizeof(float) * 12));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);
}

void Mesh::UpdateColorVectors() {
    if (colorVectors.empty()) {
        std::cerr << "ERROR: color vectors are empty" << std::endl;
        return;
    }

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, color_vectors_vbo);
    glBufferData(GL_ARRAY_BUFFER, colorVectors.size() * sizeof(glm::vec4), colorVectors.data(), GL_STREAM_DRAW);

    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void *) nullptr);

    glVertexAttribDivisor(7, 1);
}

void Mesh::loadTexture(const char * path) {
    textureId = TextureLoader::generateAndBindTexture(TextureLoader::loadTextureData(path));
}

void Mesh::loadCubeMap(const std::vector<std::string> & paths) {
    textureId = TextureLoader::loadCubeMap(paths);
}

void Mesh::loadFromResource(const std::string & path) {

    std::cout << "Loading: " << path << std::endl;

    tinyobj::attrib_t attrib;

    std::string warning;
    std::string error;

    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, path.c_str());

    if (!ret) {
        if (!error.empty()) {
            std::cerr << "Error: " << error << std::endl;
        }
    }

    if (!warning.empty()) {
        std::cout << "Mesh: " << warning << std::endl;
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