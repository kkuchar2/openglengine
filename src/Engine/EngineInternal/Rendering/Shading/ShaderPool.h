#pragma once

#include <memory>

#include "Shader.h"

class ShaderPool
{
    public:

        std::shared_ptr<Shader> colorShader;
        std::shared_ptr<Shader> diffuseShader;
        std::shared_ptr<Shader> gridShader;
        std::shared_ptr<Shader> characterShader;

        static ShaderPool & Instance()
        {
            static ShaderPool instance;

            instance.gridShader = loadShader("Grid.vert", "Grid.frag");
            instance.colorShader = loadShader("Color.vert", "Color.frag");
            instance.diffuseShader = loadShader("Diffuse.vert", "Diffuse.frag");
            instance.characterShader = loadShader("TextVert.glsl", "TextFrag.glsl");

            return instance;
        }

        static std::shared_ptr<Shader> loadShader(const std::string & vertex, const std::string & fragment) {

            std::string shadersDir = "../resources/shaders/";

            std::string vPath = shadersDir + vertex;
            std::string fPath = shadersDir + fragment;

            return std::make_shared<Shader>(vPath.c_str(), fPath.c_str());
        }

    private:
        ShaderPool() = default;



    public:
        ShaderPool(ShaderPool const&) = delete;
        void operator=(ShaderPool const&)  = delete;
};