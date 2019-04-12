#pragma once

#include <memory>

#include "Shader.h"

class ShaderPool
{
    public:

        std::shared_ptr<Shader> colorInstancedShader;
        std::shared_ptr<Shader> colorShader;
        std::shared_ptr<Shader> diffuseInstancedShader;
        std::shared_ptr<Shader> diffuseShader;
        std::shared_ptr<Shader> gridShader;
        std::shared_ptr<Shader> characterShader;

        static ShaderPool & Instance()
        {
            static ShaderPool instance;
            return instance;
        }

        static std::shared_ptr<Shader> loadShader(const std::string & vertex, const std::string & fragment) {
            std::string shadersDir = "../resources/shaders/";

            std::string vPath = shadersDir + vertex;
            std::string fPath = shadersDir + fragment;

            return std::make_shared<Shader>(vPath.c_str(), fPath.c_str());
        }

    private:
        ShaderPool() {
            gridShader = loadShader("Grid.vert", "Grid.frag");
            colorShader = loadShader("Color.vert", "Color.frag");
            colorInstancedShader = loadShader("ColorInstanced.vert", "ColorInstanced.frag");
            diffuseShader = loadShader("Diffuse.vert", "Diffuse.frag");
            diffuseInstancedShader = loadShader("DiffuseInstanced.vert", "DiffuseInstanced.frag");
            characterShader = loadShader("TextVert.glsl", "TextFrag.glsl");
        };

    public:
        ShaderPool(ShaderPool const&) = delete;

        void operator=(ShaderPool const&)  = delete;

        std::shared_ptr<Shader> getShader(const ShaderType & shaderType) {
            switch(shaderType) {
                case COLOR:   return colorShader;
                case DIFFUSE: return diffuseShader;
                case COLOR_INSTANCED: return colorInstancedShader;
                case DIFFUSE_INSTANCED: return diffuseInstancedShader;
            }
        }
};