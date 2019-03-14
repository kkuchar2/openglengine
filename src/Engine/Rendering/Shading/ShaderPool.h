#ifndef OPENGL_SHADERPOOL_H
#define OPENGL_SHADERPOOL_H

#include <memory>

#include "Shader.h"

typedef std::shared_ptr<Shader> ShaderPtr;

class ShaderPool {
    public:
            ShaderPtr colorShader;
            ShaderPtr diffuseShader;
            ShaderPtr gridShader;
            ShaderPtr characterShader;

            ShaderPool() {
                gridShader = std::make_shared<Shader>("../resources/shaders/Grid.vert", "../resources/shaders/Grid.frag");
                colorShader = std::make_shared<Shader>("../resources/shaders/Color.vert", "../resources/shaders/Color.frag");
                diffuseShader = std::make_shared<Shader>("../resources/shaders/Diffuse.vert", "../resources/shaders/Diffuse.frag");
                characterShader = std::make_shared<Shader>("../resources/shaders/TextVert.glsl", "../resources/shaders/TextFrag.glsl");
            }
};

#endif //OPENGL_SHADERPOOL_H