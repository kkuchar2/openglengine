#pragma once

#include <memory>

#include "Shader.h"

typedef std::shared_ptr<Shader> ShaderPtr;
class ShaderPool
{
    public:

        ShaderPtr colorShader;
        ShaderPtr diffuseShader;
        ShaderPtr gridShader;
        ShaderPtr characterShader;

        static ShaderPool & Instance()
        {
            static ShaderPool instance;

            instance.gridShader = loadShader("Grid.vert", "Grid.frag");
            instance.colorShader = loadShader("Color.vert", "Color.frag");
            instance.diffuseShader = loadShader("Diffuse.vert", "Diffuse.frag");
            instance.characterShader = loadShader("TextVert.glsl", "TextFrag.glsl");

            return instance;
        }
    private:
        ShaderPool() = default;

        static std::shared_ptr<Shader> loadShader(const std::string & vertex, const std::string & fragment) {

            std::string shadersDir = "../resources/shaders/";

            std::string vPath = shadersDir + vertex;
            std::string fPath = shadersDir + fragment;

            return std::make_shared<Shader>(vPath.c_str(), fPath.c_str());
        }

    public:
        ShaderPool(ShaderPool const&) = delete;
        void operator=(ShaderPool const&)  = delete;
};