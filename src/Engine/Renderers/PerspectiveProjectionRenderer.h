#ifndef OPENGL_PERSPECTIVEPROJECTIONRENDERER_H
#define OPENGL_PERSPECTIVEPROJECTIONRENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>

#include "../Window.h"
#include "../Primitives/RenderObject.h"
#include "../Shader.h"

class PerspectiveProjectionRenderer {
    private:
        Window * window;

    public:
        PerspectiveProjectionRenderer(Window * window) {
            this->window = window;
        }

        void Render(RenderObject & renderObject, std::function<void(const Shader *)> postShaderSetupFunc) {
            Shader * shader = renderObject.shader;

            shader->use();
            shader->setMat4("projection", glm::perspective(glm::radians(45.0f), window->aspectRatio, 0.1f, 1000.0f));
            shader->setMat4("view", glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0)));
            shader->setMat4("model",  glm::mat4(1.0));

            shader->setVec3("translation", renderObject.position);
            shader->setVec3("scale", renderObject.scale);
            shader->setVec3("rotation", renderObject.rotation);

            postShaderSetupFunc(shader);

            renderObject.Render();
        }

};

#endif //OPENGL_PERSPECTIVEPROJECTIONRENDERER_H
