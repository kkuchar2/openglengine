#pragma once

#include <memory>

#include "Shader.h"

class ShaderPool
{
    public:

        std::shared_ptr<Shader> textureCubeShader;
        std::shared_ptr<Shader> textureColorShader;
        std::shared_ptr<Shader> colorInstancedShader;
        std::shared_ptr<Shader> colorShader;
        std::shared_ptr<Shader> diffuseInstancedShader;
        std::shared_ptr<Shader> diffuseShader;
        std::shared_ptr<Shader> fastDiffuseShader;
        std::shared_ptr<Shader> gridShader;
        std::shared_ptr<Shader> gridInstancedShader;
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
            gridInstancedShader = loadShader("GridInstanced.vert", "GridInstanced.frag");
            colorShader = loadShader("Color.vert", "Color.frag");
            colorInstancedShader = loadShader("ColorInstanced.vert", "ColorInstanced.frag");
            diffuseShader = loadShader("Diffuse.vert", "Diffuse.frag");
            fastDiffuseShader = loadShader("FastDiffuse.vert", "Diffuse.frag");
            diffuseInstancedShader = loadShader("DiffuseInstanced.vert", "DiffuseInstanced.frag");
            mandelbrotShader = loadShader("Mandelbrot.vert", "Mandelbrot.frag");
        };

    public:
        ShaderPool(ShaderPool const&) = delete;

        void operator=(ShaderPool const&)  = delete;

        std::shared_ptr<Shader> getShader(const ShaderType & shaderType) {
            switch(shaderType) {
                case COLOR: return colorShader;
                case DIFFUSE: return diffuseShader;
                case COLOR_INSTANCED: return colorInstancedShader;
                case DIFFUSE_INSTANCED: return diffuseInstancedShader;
                case GRID: return gridShader;
                case GRID_INSTANCED: return gridInstancedShader;
                case TEXTURE: return textureColorShader;
                case TEXTURE_CUBE: return textureCubeShader;
                case FAST_DIFFUSE: return fastDiffuseShader;
                case MANDELBROT: return mandelbrotShader;
            }
        }
};