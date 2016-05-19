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

    /* 
        Sets up a QApplication
        with the proper formatting. This allows
        GL versions to be set and so forth. Then
        the QApplication is polled in the main loop
        for events.
    */

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
    EditorRenderer editor(engine, WIDTH, HEIGHT);

    editor.resize(WIDTH, HEIGHT);
    editor.show();

    /* 
        Must call EditorRenderer.show() before any other
        OpenGL calls. This is mostly because of Qt.
    */

    auto house = new Model("/home/lasacs/Desktop/engine/res/farm house/OBJ/Farmhouse OBJ.obj", "/home/lasacs/Desktop/engine/res/farm house/Textures/Farmhouse Texture.jpg");

    house->transform->getPosition()->z = 40;
    auto model = new Model("/home/lasacs/Desktop/engine/res/Alfred/Alfred.obj", "/home/lasacs/Desktop/engine/res/Alfred/alfred_dif.png");

    editor.addModel(house);
    editor.addModel(model);

    float counter = 0.0f;

    while (editor.isVisible())
    {
        app.processEvents();
        model->transform->getRotation()->y = counter;
        counter += 0.1f;

        editor.update();
    }

    return 0;
}
