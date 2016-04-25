#include <stdio.h>
#include <vector>
#include "OpenGL/gl3.h"
#include "window.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"

#define WIDTH 800
#define HEIGHT 600

bool quit = false;

int main()
{
	/////// Mesh data
	std::vector<GLuint> elements =  {
	        0, 1, 2,
	        2, 3, 0
	    };

	std::vector<float> vertices =  {
			-0.5f,  0.5f, 0.0f,  	// Top-left
			 0.5f,  0.5f, 0.0f,  // Top-right
			 0.5f, -0.5f, 0.0f, 	// Bottom-right
			-0.5f, -0.5f, 0.0f	// Bottom-left
	};


	std::vector<float> texCoords =  {
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
	};

	//////////////////
    auto win = Window(640, 480);
    auto shaders = Shader("./res/shaders/shader");

    // test ModelData
    struct ModelData mData(vertices, texCoords, elements);


    auto mesh = Mesh(mData);
    auto tex = Texture();
    auto trans = Transform();
    auto cam = Camera(glm::vec3(0, 0, -3), 70.0f, (float) WIDTH / (float) HEIGHT, 0.01f, 1000.0f);

    float counter = 0.0f;

    while (!win.close())
    {
        win.clear(0.2, 0.5, 0.8, 1.0);

        // trans.getPosition()->x = sinf(counter);
        // trans.getRotation()->z = cosf(counter * 50);

        shaders.draw();
        shaders.update(trans, cam);
        mesh.draw();
        glfwSwapBuffers(win.getWindow());
        glfwPollEvents();

        counter += 0.01f;
    }
}
