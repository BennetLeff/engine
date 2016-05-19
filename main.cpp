#include <stdio.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include "Camera.h"
#include "Model.h"

#include "EditorRenderer.h"
#include "RenderEngine.h"

#include <QApplication>

bool quit = false;

int main(int argc, char* argv[])
{
    int WIDTH = 800;
    int HEIGHT = 600;

    QApplication app(argc, argv);
    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    auto cam = new Camera(glm::vec3(0, 6, -20), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);
    RenderEngine engine(cam);
    engine.init();
    EditorRenderer widget(engine, WIDTH, HEIGHT);

    widget.resize(WIDTH, HEIGHT);
    widget.show();

    return app.exec();
}
