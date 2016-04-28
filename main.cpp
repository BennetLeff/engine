#include <stdio.h>
#include <vector>
#include "OpenGL/gl3.h"
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "MeshImporter.h"

#define WIDTH 800
#define HEIGHT 600

bool quit = false;

int main()
{
    auto win = Window(640, 480);
    auto shaders = Shader("./res/shaders/shader");

    // test ModelData
    auto meshLoad = MeshImporter("./res/deer-obj/deer-obj.obj");
    auto mesh = Mesh(meshLoad.meshes[0].positions, meshLoad.meshes[0].textures, meshLoad.meshes[0].elms);

    auto tex = Texture();
    auto trans = Transform();
    auto cam = Camera(glm::vec3(0, 15, -40), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);

    float counter = 0.0f;

    while (!win.close())
    {
        win.clear(0.2, 0.5, 0.8, 1.0);

        trans.getRotation()->y = 225;
        shaders.draw();
        shaders.update(trans, cam);

        mesh.draw();

        glfwSwapBuffers(win.getWindow());
        glfwPollEvents();

        counter += 0.01f;
    }
}
