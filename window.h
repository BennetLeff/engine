#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"

class Window
{
public:
    void update();
    // sets the color for the buffer clear
    void clear(float red, float green, float blue, float alpha);
    // returns glfw window
    GLFWwindow* getWindow();
    // should the window close
    bool close();
    Window(int width, int height);
    ~Window();
private:
    GLFWwindow* window;
};