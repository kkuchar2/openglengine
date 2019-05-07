#include "MeshRenderer.h"

#include <Utils/NormalsGenerator/NormalsGenerator.h>
#include <Rendering/Shading/ShaderPool.h>

void MeshRenderer::init(const std::shared_ptr<Mesh> & m) {
    mesh = m;
}

void MeshRenderer::prepare() {

    /// Verify if associated mesh exists
    if (!mesh.get()) {
        std::cerr << "MeshRenderer: Mesh is NULL" << std::endl;
    }

    /// Ignore if mesh already prepared
    if (mesh->prepared) {
        std::cout << "Mesh already prepared" << std::endl;
        return;
    }

    /// Load shader
    shader = ShaderPool::Instance().getShader(shaderType);


    /// Setup shader update method
    shaderInit = [](const std::shared_ptr<Shader> & s) {
        s->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        s->setVec3("lightPos", glm::vec3(2.2f, 3.0f, 2.0f));
    };

    /// Load textures
    if (texture != nullptr) {
        loadTexture(texture);
    }
    else if (paths.size() > 0) {
        loadCubeMap(paths);
    }

    /// Generate normals for mesh if required
    if (!disableNormals) {
        NormalsGenerator::generate(mesh.get());
    }

    /// Prepare GPU buffers and initialize them
    CreateVertexAttributeObject();
    CreateIndexBuffer();
    CreateVertexBuffer();
    CreateUVBuffer();
    CreateNormalsBuffer();
    CreateModelMatricesBuffer();
    CreateColorBuffer();

    glBindVertexArray(0);

    mesh->prepared = true;
}


void MeshRenderer::CreateVertexAttributeObject() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void MeshRenderer::CreateIndexBuffer() {
    auto indices = mesh->indices;

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void MeshRenderer::CreateVertexBuffer() {

    auto vertices = mesh->vertices;

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


void MeshRenderer::CreateUVBuffer() {

    auto uvs = mesh->uvs;

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

void MeshRenderer::CreateNormalsBuffer() {

    auto normals = mesh->normals;

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

void MeshRenderer::CreateModelMatricesBuffer() {

    auto modelMatrices = mesh->modelMatrices;

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

void MeshRenderer::UpdateModelMatrices() {

    auto modelMatrices = mesh->modelMatrices;

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

void MeshRenderer::CreateColorBuffer() {

    auto colorVectors = mesh->colorVectors;

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

void MeshRenderer::UpdateColorVectors() {

    auto colorVectors = mesh->colorVectors;

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

void MeshRenderer::loadTexture(const char * path) {
    std::cout << "Loading texture: " << path << std::endl;
    textureId = TextureLoader::generateAndBindTexture(TextureLoader::loadTextureData(path));
    std::cout << "Texture id: " << textureId << std::endl;
}

void MeshRenderer::loadCubeMap(const std::vector<std::string> & paths) {
    std::cout << "Loading cube map textures" << std::endl;


    for (auto & path : paths) {
        std::cout << "\tLoading texture: " << path << std::endl;
    }

    textureId = TextureLoader::loadCubeMap(paths);

    std::cout << "Texture id: " << textureId << std::endl;
}

void MeshRenderer::render() {
    render(mesh->renderingMode, static_cast<int>(mesh->indices.size()));
}

void MeshRenderer::renderInstanced(int instancesCount) {
    renderInstanced(mesh->renderingMode, static_cast<int>(mesh->indices.size()), instancesCount);
}

void MeshRenderer::render(GLenum renderMode, int indicesCount) {
    glBindTexture(cubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, textureId);
    glBindVertexArray(vao);
    glDrawElements(renderMode, indicesCount, GL_UNSIGNED_INT, (void *) nullptr);
}

void MeshRenderer::renderInstanced(GLenum renderMode, int indicesCount, int instancesCount) {
    glBindTexture(cubeMap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, textureId);
    glBindVertexArray(vao);
    glDrawElementsInstanced(renderMode, indicesCount, GL_UNSIGNED_INT, (void *) nullptr, instancesCount);
}

std::string MeshRenderer::getShaderTypeStr() {
    switch(shaderType) {
        case AMBIENT: return "ambient";
        case PHONG: return "phong";
        case GRID: return "grid";
        case TEXTURE: return "texture";
        case TEXTURE_CUBE: return "texture_cube";
        case MANDELBROT: return "mandelbrot";
    }
}