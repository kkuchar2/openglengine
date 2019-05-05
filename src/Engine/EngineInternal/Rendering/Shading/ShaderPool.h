#pragma once

#include <memory>

#include "Shader.h"
#include "ShaderType.h"

class ShaderPool
{
    public:

        std::shared_ptr<Shader> textureCubeShader;
        std::shared_ptr<Shader> textureColorShader;
        std::shared_ptr<Shader> ambientShader;
        std::shared_ptr<Shader> phongShader;
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
            textureCubeShader = loadShader("TexturedCube/TexturedCube.vert", "TexturedCube/TexturedCube.frag");
            textureColorShader = loadShader("Textured/Textured.vert", "Textured/Textured.frag");
            gridShader = loadShader("Grid/Grid.vert", "Grid/Grid.frag");
            ambientShader = loadShader("Ambient/Ambient.vert", "Ambient/Ambient.frag");
            phongShader = loadShader("Phong/Phong.vert", "Phong/Phong.frag");
            mandelbrotShader = loadShader("Mandelbrot/Mandelbrot.vert", "Mandelbrot/Mandelbrot.frag");
        };

    public:
        ShaderPool(ShaderPool const&) = delete;

        void operator=(ShaderPool const&)  = delete;

        std::shared_ptr<Shader> getShader(const ShaderType & shaderType) {
            switch(shaderType) {
                case AMBIENT: return ambientShader;
                case PHONG: return phongShader;
                case GRID: return gridShader;
                case TEXTURE: return textureColorShader;
                case TEXTURE_CUBE: return textureCubeShader;
                case MANDELBROT: return mandelbrotShader;
            }
        }
};