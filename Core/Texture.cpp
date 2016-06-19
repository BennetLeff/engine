#include <string>

#ifndef STB_IMAGE_H_
    #define STB_IMAGE_IMPLEMENTATION
    #include "lib/stb_image.h"
#endif

#include "Texture.h"

Texture::Texture(std::string textureFile)
{
    mFilePath = QString(textureFile.data());
    if(fileExists(mFilePath.toStdString()))
    {
        // Generate and bind texture.
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        // Set wrapping parameters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);

        // Set scaling filters.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        // Use stb_image to load images.
        image = stbi_load(mFilePath.toStdString().c_str(), &width, &height, &comp, STBI_rgb);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, image);

        stbi_image_free(image);
    }
}

void Texture::bind(GLuint unit)
{
    // activates the texture numbered as unit
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, tex);
}

bool Texture::fileExists(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}