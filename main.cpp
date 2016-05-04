#include <stdio.h>
#include <vector>
#include "OpenGL/gl3.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "Input.h"

#define WIDTH 800
#define HEIGHT 600

bool quit = false;

int main()
{
    auto win = Window(640, 480);

    auto cam = new Camera(glm::vec3(0, 5, -15), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);

    float counter = 0.0f;

    auto model = Model("./res/Alfred/Alfred.obj", "./res/Alfred/alfred_dif.png");
    auto house = Model("./res/farm house/OBJ/Farmhouse OBJ.obj", "./res/farm house/Textures/Farmhouse Texture.jpg");
    model.transform->getPosition()->z = 10;
    house.transform->getPosition()->z = 40;

    auto iManager = Input(win.getWindow());

    while (!win.close() && !quit)
    {
        win.clear(0.2, 0.5, 0.8, 1.0);

        model.draw(cam);
        house.draw(cam);
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

        glfwSwapBuffers(win.getWindow());
        glfwPollEvents();

        counter += 0.01f;
    }
}
