#include <Window/Input/Mouse.h>
#include <Window/Window.h>
#include <stdio.h>
#include <math.h>

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

bool mouseIsOverRect(Mouse * mouse, Vec2u rectPosition, Vec2u rectSize)
{
    if(mouse->position.x > rectPosition.x
    && mouse->position.x < rectPosition.x + rectSize.x
    && mouse->position.y > rectPosition.y
    && mouse->position.y < rectPosition.y + rectSize.y)
        return true;
    return false;
}
bool mouseIsOverRadius(Mouse * mouse, Vec2u position, float radius)
{
    int diffx = abs(position.x - mouse->position.x);
    int diffy = abs(position.y - mouse->position.y);
    int diffxp2 = diffx * diffx;
    int diffyp2 = diffy * diffy;
    int distance = sqrt(diffxp2 + diffyp2);
    if(distance <= radius)
    {
        return true;
    }
    return false;
}