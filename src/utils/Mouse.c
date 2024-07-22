#include <utils/Mouse.h>

struct Mouse Mouse;

void mouseButtonUpdate(GLFWwindow * window)
{
    Mouse.button.left.clickdown = false;
    Mouse.button.left.clickup = false;
    Mouse.button.left.clickdown = false;
    Mouse.button.left.clickup = false;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        if(!Mouse.button.left.clicked)
        {
            Mouse.button.left.clicked = true;
            Mouse.button.left.clickdown = true;
        }
    }
    else
    {
        if(Mouse.button.left.clicked)
        {
            Mouse.button.left.clicked = false;
            Mouse.button.left.clickup = true;
        }
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
    {
        if(!Mouse.button.right.clicked)
        {
            Mouse.button.right.clicked = true;
            Mouse.button.right.clickdown = true;
        }
    }
    else
    {
        if(Mouse.button.right.clicked)
        {
            Mouse.button.right.clicked = false;
            Mouse.button.right.clickup = true;
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    Mouse.x = xpos;
    Mouse.y = ypos;
}