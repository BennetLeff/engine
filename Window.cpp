#include <stdio.h>
#include "Window.h"

void Window::clear(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::close()
{
    return glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow()
{
    return window;
}

Window::Window(int width, int height)
{
    // If not on OSX we need to include
    // OpenGL as an extension
    #ifndef __APPLE__
        glewExperimental = GL_TRUE;

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
          /* Problem: glewInit failed, something is seriously wrong. */
          fprintf(stderr, "Error: %s\n", glewGetErrorString(err)); 
        }        
    #endif

    if (!glfwInit())
        printf("GLFW could not be initialized. A window could not be created.\n");

    // Necessary window hints to make OSX happy.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


    window = glfwCreateWindow(640, 480, "Window", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        printf("Window could not be created. \n");
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
