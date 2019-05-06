#include <glad.h>
#include "Mesh.h"

#include <Components/Component.h>

class MeshRenderer : public Component {

    private:

        std::shared_ptr<Mesh> mesh;

        GLuint vao = 0;
        GLuint vbo = 0;
        GLuint uvbo = 0;
        GLuint nbo = 0;
        GLuint model_matrices_vbo = 0;
        GLuint color_vectors_vbo = 0;
        GLuint ibo = 0;

        GLuint textureId = 0;

    public:

        void init(const std::shared_ptr<Mesh> & mesh);

        void prepare();

        void CreateVertexAttributeObject();
        void CreateIndexBuffer();
        void CreateVertexBuffer();
        void CreateUVBuffer();
        void CreateNormalsBuffer();
        void CreateModelMatricesBuffer();
        void CreateColorBuffer();

        void UpdateModelMatrices();
        void UpdateColorVectors();

        void loadTexture(const char * path);
        void loadCubeMap(const std::vector<std::string> & paths);

        void render();
        void renderInstanced(int instancesCount);
        void renderInstanced(GLenum renderMode, int indicesCount, int instanceCount);
        void render(GLenum renderMode, int indicesCount);
};