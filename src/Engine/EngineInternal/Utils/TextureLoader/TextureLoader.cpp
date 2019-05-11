#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image/stb_image.h"

TextureInfo TextureLoader::loadTextureData(const char * path) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data = stbi_load(path, &width, &height, &nrChannels, 0);
    TextureInfo info {};
    info.data = data;
    info.width = width;
    info.height = height;
    return info;
}

GLuint TextureLoader::loadCubeMap(const std::vector<std::string> & paths) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;

    unsigned char * data;

    for (GLuint i = 0; i < 6; i++) {
        data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

GLuint TextureLoader::generateAndBindTexture(const TextureInfo & info) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.width, info.height, 0, GL_RGB, GL_UNSIGNED_BYTE, info.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return textureID;
}


