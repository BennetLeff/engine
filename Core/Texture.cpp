#include <string>

#include "Texture.h"

Texture::Texture(std::string textureFile)
{
    mFilePath = QString(textureFile.data());
    if(fileExists(mFilePath.toStdString()))
    {
        mImage = QImage();

        mImage.load(mFilePath);

        // Make sure valid image loaded
        if(mImage.byteCount() > 0)
            mTexture = new QOpenGLTexture(mImage);
    }
}

void Texture::bind(GLuint unit)
{
    // Activates the texture numbered as unit so long as image exists.
    if(mImage.byteCount() > 0)
        mTexture->bind(unit);
}

bool Texture::fileExists(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}