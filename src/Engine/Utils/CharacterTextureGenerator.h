#ifndef OPENGL_TEXTRENDERER_H
#define OPENGL_TEXTRENDERER_H

#include <ft2build.h>
#include "freetype/freetype.h"

struct Character {
    GLuint     TextureID;  // ID handle of the glyph texture
    glm::ivec2 Size;       // Size of glyph
    glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
    GLuint     Advance;    // Offset to advance to next glyph
};

class CharacterTextureGenerator {

    public:
        std::map<GLchar, Character> Characters;

        FT_Library ft{};
        FT_Face face{};

        CharacterTextureGenerator() {
           InitializeFreeType();
        }

        void InitializeFreeType() {


            if (FT_Init_FreeType(&ft)) {
                fprintf(stderr, "Could not init freetype library\n");
            }
        }

        void loadFont(const char * path) {


            if (FT_New_Face(ft, path, 0, &face)) {
                std::stringstream ss;
                ss << "Could not open font: " << path;

                Logger::Log(ERROR, this, ss);
            }
        }

        void setFontSize(FT_UInt size) {
            FT_Set_Pixel_Sizes(face, 0, size);
        }

        void init() {
            for (GLubyte c = 0; c < 128; c++)
            {
                // Load character glyph
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                    continue;
                }
                // Generate texture
                GLuint texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                        GL_TEXTURE_2D,
                        0,
                        GL_RED,
                        face->glyph->bitmap.width,
                        face->glyph->bitmap.rows,
                        0,
                        GL_RED,
                        GL_UNSIGNED_BYTE,
                        face->glyph->bitmap.buffer
                );
                // Set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // Now store character for later use
                Character character = {
                        texture,
                        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                        static_cast<GLuint>(face->glyph->advance.x)
                };
                Characters.insert(std::pair<GLchar, Character>(c, character));
            }
        }
};

#endif //OPENGL_TEXTRENDERER_H