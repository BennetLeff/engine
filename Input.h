#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class Input
{
public:
    Input(GLFWwindow* window)
    {
        this->window = window;
    }

    bool keyAction(int key, int action)
    {
        if (glfwGetKey(window, key) == action)
            return true;
        return false;
    }

    bool keyDown(int key)
    {
        // Action code 1 = PRESS
        if (glfwGetKey(window, key) == 1)
            return true;
        return false;
    }

    enum Action 
    {
        PRESS = 1
    };

    enum Key
    {
        SPACE = 32,
        A = 65,
        B, C, D, E, F,
        G, H, I, J, K,
        L, M, N, O, P,
        Q, R, S, T, U,
        V, W, X, Y, Z,
        ESC = 256
    };

private:
    GLFWwindow* window;
};