#include <Window/Input/Mouse.h>
#include <Window/Window.h>
#include <stdio.h>

Mouse * mouseCreate()
{
    Mouse * out = malloc(sizeof(Mouse));
    out->position.x = 0;
    out->position.y = 0;
    out->button.left.clicked = false;
    out->button.left.clickdown = false;
    out->button.left.clickup = false;
    out->button.right.clicked = false;
    out->button.right.clickdown = false;
    out->button.right.clickup = false;
    return out;
}

void mouseButtonUpdate(GLFWwindow * window, Mouse * mouse)
{
    mouse->button.left.clickdown = false;
    mouse->button.left.clickup = false;
    mouse->button.left.clickdown = false;
    mouse->button.left.clickup = false;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        if(!mouse->button.left.clicked)
        {
            mouse->button.left.clicked = true;
            mouse->button.left.clickdown = true;
        }
    }
    else
    {
        if(mouse->button.left.clicked)
        {
            mouse->button.left.clicked = false;
            mouse->button.left.clickup = true;
        }
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
    {
        if(!mouse->button.right.clicked)
        {
            mouse->button.right.clicked = true;
            mouse->button.right.clickdown = true;
        }
    }
    else
    {
        if(mouse->button.right.clicked)
        {
            mouse->button.right.clicked = false;
            mouse->button.right.clickup = true;
        }
    }
}

void cursor_position_callback(GLFWwindow* win, double x, double y)
{
    Window* window = (Window*)glfwGetWindowUserPointer(win);
    window->mouse->position.x = x;
    window->mouse->position.y = y;
}