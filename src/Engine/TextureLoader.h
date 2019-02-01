#ifndef OPENGL_BMPLOADER_H
#define OPENGL_BMPLOADER_H

#include <cstdio>
#include <iostream>
#include <deps/glad/glad.h>

class TextureLoader {
    public:
        static GLuint load(const char * path) {
            unsigned char header[54];
            int dataPos;
            int width, height;
            int imageSize;

            unsigned char * data;

            FILE * file = fopen(path, "rb");

            if (!file) {
                std::cerr << "Could not open " << path << std::endl;
                return 0;
            }

            if (fread(header, 1, 54, file) != 54) {
                std::cerr << "Invalid BMP file: " << path << std::endl;
                return 0;
            }

            if ( header[0] != 'B' || header[1] != 'M' ){
                std::cerr << "Invalid BMP file: " << path << std::endl;
                return 0;
            }

            imageSize  = *(int*)&(header[0x22]);
            width      = *(int*)&(header[0x12]);
            height     = *(int*)&(header[0x16]);

            std::cout << "Image size: " << imageSize << std::endl;
            std::cout << "Image width: " << width << std::endl;
            std::cout << "Image height: " << height << std::endl;

            if (imageSize == 0) {
                imageSize = width * height * 3;
            }


            data = new unsigned char [imageSize];

            fread(data, 1, imageSize, file);

            fclose(file);

            GLuint textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

            return textureID;
        }
};

#endif //OPENGL_BMPLOADER_H
