#pragma once

#include <cstdio>
#include <iostream>
#include <glad.h>
#include <vector>

struct TextureInfo {
    int width;
    int height;
    unsigned char * data;
};

class TextureLoader {
    public:
        static TextureInfo loadTextureData(const char * path);
        static GLuint loadCubeMap(const std::vector<std::string> & paths);
        static GLuint generateAndBindTexture(const TextureInfo & info);
};