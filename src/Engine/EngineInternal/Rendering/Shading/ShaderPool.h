#pragma once

#include <memory>

#include "Shader.h"

class ShaderPool
{
    public:

        std::shared_ptr<Shader> textureCubeShader;
        std::shared_ptr<Shader> textureColorShader;
        std::shared_ptr<Shader> colorShader;
        std::shared_ptr<Shader> diffuseShader;
        std::shared_ptr<Shader> gridShader;
        std::shared_ptr<Shader> mandelbrotShader;

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
            textureCubeShader = loadShader("TexturedCube.vert", "TexturedCube.frag");
            textureColorShader = loadShader("Textured.vert", "Textured.frag");
            gridShader = loadShader("Grid.vert", "Grid.frag");
            colorShader = loadShader("Color.vert", "Color.frag");
            diffuseShader = loadShader("Diffuse.vert", "Diffuse.frag");
            mandelbrotShader = loadShader("Mandelbrot.vert", "Mandelbrot.frag");
        };

    public:
        ShaderPool(ShaderPool const&) = delete;

        void operator=(ShaderPool const&)  = delete;

        std::shared_ptr<Shader> getShader(const ShaderType & shaderType) {
            switch(shaderType) {
                case COLOR: return colorShader;
                case DIFFUSE: return diffuseShader;
                case GRID: return gridShader;
                case TEXTURE: return textureColorShader;
                case TEXTURE_CUBE: return textureCubeShader;
                case MANDELBROT: return mandelbrotShader;
            }
        }
};