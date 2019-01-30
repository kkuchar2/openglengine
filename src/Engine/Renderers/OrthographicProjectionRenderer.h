#ifndef OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H
#define OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>

#include "../Window.h"
#include "../Primitives/RenderObject.h"

class OrtographicProjectionRenderer {
    private:
        Window * window;

    public:
        OrtographicProjectionRenderer(Window * window) {
            this->window = window;
        }

        void Render(RenderObject & renderObject, std::function<void(const Shader *)> postShaderSetupFunc) {

            Shader * shader = renderObject.shader;
            shader->use();

            shader->setMat4("projection", glm::ortho(
                    -(float) window->width,
                    (float) window->width,
                    (float) window->height,
                    -(float) window->height,
                    -1000.0f,
                    1000.0f
            ));
            shader->setMat4("view", glm::mat4(1.0));


            glm::mat4 model = glm::mat4(1.0);
            model = glm::scale(model, glm::vec3(window->width - 1, window->height - 1, 1.0f));
            model = glm::scale(model, renderObject.scale);

            shader->setMat4("model",  model);

            shader->setVec3("translation", renderObject.position);
            shader->setVec3("scale", renderObject.scale);
            shader->setVec3("rotation", renderObject.rotation);

            postShaderSetupFunc(shader);

            renderObject.Render();
        }

};

#endif //OPENGL_ORTHOGRAPHICPROJECTIONRENDERER_H
