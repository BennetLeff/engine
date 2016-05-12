#include <stdio.h>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include "Camera.h"
#include "Model.h"
#include "Window.h"
#include "Input.h"

#include "GUI.h"

bool quit = false;

int main()
{
    int WIDTH = 800;
    int HEIGHT = 600;

    auto gui = GUI(WIDTH, HEIGHT);

    auto cam = new Camera(glm::vec3(0, 6, -15), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);

    float counter = 0.0f;

    auto model = Model("./res/Alfred/Alfred.obj", "./res/Alfred/alfred_dif.png");
    auto house = Model("./res/farm house/OBJ/Farmhouse OBJ.obj", "./res/farm house/Textures/Farmhouse Texture.jpg");
    auto ground = Model("./res/plane/plane.obj", "./res/plane/grass.jpg");

    model.transform->getPosition()->z = 10;
    model.transform->setScale(glm::vec3(0.75));
    house.transform->getPosition()->z = 40;
    ground.transform->getPosition()->y -= 0.2;
    ground.transform->getPosition()->z = 30;
    ground.transform->getScale()->z = 10;
    ground.transform->getScale()->x = 10;

    auto iManager = Input(gui.getWindow());

    while (!gui.close() && !quit)
    {
        gui.clear(0.2, 0.5, 0.8, 1.0);

        model.draw(cam);
        house.draw(cam);
        ground.draw(cam);

        gui.drawAll();

        gui.setVisible(true);

        model.transform->getRotation()->y = counter * 2;

        if (iManager.keyAction(iManager.A, iManager.PRESS))
            cam->getPosition()->x += 1;
        if (iManager.keyAction(iManager.D, iManager.PRESS))
            cam->getPosition()->x -= 1;
        if (iManager.keyAction(iManager.W, iManager.PRESS))
            cam->getPosition()->z += 1;
        if (iManager.keyAction(iManager.S, iManager.PRESS))
            cam->getPosition()->z -= 1;
        if (iManager.keyAction(iManager.SPACE, iManager.PRESS))
            cam->getPosition()->y += 1;
        if (iManager.keyAction(iManager.Z, iManager.PRESS))
            cam->getPosition()->y -= 1;
        if (iManager.keyAction(iManager.ESC, iManager.PRESS))
            quit = true;

        glfwSwapBuffers(gui.glfwWindow());
        glfwPollEvents();

        counter += 0.01f;
    }
}
