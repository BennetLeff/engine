#pragma once
#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include <QObject>
#include <QImage>
#include <fstream>

#include <QOpenGLTexture>

class Texture : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Path MEMBER mFilePath)
public:
    Texture(std::string filePath);
    void bind(GLuint unit);
    // Call when a texture should be reset like when the file path changes.
    bool textureFilePathValid() { return fileExists(mFilePath.toStdString()); }
    bool fileExists(const std::string& name);
    QImage* getImage() { return &mImage; }
private:
    QString mFilePath = "";
    QImage mImage;
    QOpenGLTexture* mTexture;
};