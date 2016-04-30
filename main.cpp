#include <stdio.h>
#include <vector>
#include "OpenGL/gl3.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

#define WIDTH 800
#define HEIGHT 600

bool quit = false;

int main()
{
    auto win = Window(640, 480);

    auto cam = Camera(glm::vec3(0, 15, -40), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);

    float counter = 0.0f;

    Model model = Model("./res/deer-obj/deer-obj.obj", "./res/deer-obj/deer texture.tga");    
    Model model2 = Model("./res/deer-obj/deer-obj.obj", "./res/brick.jpg");

    model.transform->getRotation()->y = 225;
    model2.transform->getRotation()->y = 235;

    model.transform->getPosition()->x = -5;
    model2.transform->getPosition()->x = 5;

    while (!win.close())
    {
        win.clear(0.2, 0.5, 0.8, 1.0);


        model.draw(cam);
        model2.draw(cam);

        glfwSwapBuffers(win.getWindow());
        glfwPollEvents();

        counter += 0.1f;
    }
}
