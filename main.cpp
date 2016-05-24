#include <stdio.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include "Camera.h"
#include "Model.h"

#include "Editor.h"
#include "RenderEngine.h"

#include <QApplication>

bool quit = false;

int main(int argc, char* argv[])
{
    auto WIDTH = 1024;
    auto HEIGHT = 800;

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
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    // Sets up Rendering Engine and Editor.
    auto cam = new Camera(glm::vec3(0, 6, -20), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);
    RenderEngine* engine = new RenderEngine(cam);
    Editor editor(engine, WIDTH, HEIGHT);

    editor.showEditor();

    /*
     * Must call Editor.show() before any other
     * OpenGL calls. This is mostly because of Qt.
    */
    auto house = Model("./res/farm house/OBJ/Farmhouse OBJ.obj", "./res/farm house/Textures/Farmhouse Texture.jpg");
    house.transform->getPosition()->z = 40;
//
    auto model = Model("./res/Alfred/Alfred.obj", "./res/Alfred/alfred_dif.png");
//    auto mod1 = Model("./res/deer-obj/deer-obj.obj", "./res/deer-obj/deer texture.tga");
//    auto mod2 = Model("./res/deer-obj/deer-obj.obj", "./res/deer-obj/deer texture.tga");
//    auto mod3 = Model("./res/deer-obj/deer-obj.obj", "./res/deer-obj/deer texture.tga");
//
    editor.addModel(house);
    editor.addModel(model);

    float counter = 0.0f;

    while (editor.isVisible())
    {
        app.processEvents();
        model.transform->getRotation()->y = float(editor.getSliderValue()) / 10;
        model.transform->getPosition()->z = editor.getManValue();
//        model.transform->setPosition(glm::vec3(0, float(editor.getSliderValue()) / 10, editor.getManValue()));
//        mod1.transform->getPosition()->z  = editor.getManValue();
        counter += 0.1f;

        /*
         * Just updating window for now because
         * it may be faster. Need to benchmark this
         * and determine what is necessary.
        */
        editor.getWindow()->update();
    }

    return 0;
}
