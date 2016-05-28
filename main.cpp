#include <stdio.h>

#include <QApplication>

#include "Camera.h"
#include "Model.h"
#include "Editor.h"

int main(int argc, char* argv[])
{
    auto WIDTH = 1400;
    auto HEIGHT = 900;

    /* 
     * Sets up a QApplication
     * with the proper formatting. This allows
     * GL versions to be set and so forth. Then
     * the QApplication is polled in the main loop
     * for events.
    */
    QApplication app(argc, argv);
    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    // Sets up Camera, Rendering Engine and Editor.
    auto cam = new Camera(glm::vec3(0, 6, -20), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);
    RenderEngine* engine = new RenderEngine(cam);
    Editor editor(engine, WIDTH, HEIGHT);

    /*
     * Must call Editor.show() before any other
     * OpenGL calls. This is mostly because of Qt.
    */
    editor.showEditor();

    auto house = Model("./res/farm house/OBJ/Farmhouse OBJ.obj", "./res/farm house/Textures/Farmhouse Texture.jpg");
    house.transform->getPosition()->z = 40;

    auto model = Model("./res/Alfred/Alfred.obj", "./res/Alfred/alfred_dif.png");

    editor.addModel(house);
    editor.addModel(model);

    while (editor.isVisible())
    {
        app.processEvents();

        /*
         * Just updating window for now because
         * it may be faster. Need to benchmark this
         * and determine what is necessary.
        */
         editor.getWindow()->update();
    }

    return 0;
}
