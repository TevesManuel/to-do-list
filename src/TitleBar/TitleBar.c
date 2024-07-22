#include <TitleBar/TitleBar.h>
#include <utils/Mouse.h>
#include <Config.h>
#include <GLFW/glfw3.h>

struct TitleBar TitleBar;

void titleBarUpdate(GLFWwindow * window)
{
    if(Mouse.button.left.clickdown && Mouse.y < APP_WINDOW_HEIGHT*0.05)
    {
        TitleBar.dragged = true;
    
        TitleBar.rx = Mouse.x;
        TitleBar.ry = Mouse.y;
    }
    if(TitleBar.dragged)
    {
        int xpos, ypos;
        glfwGetWindowPos(window, &xpos, &ypos);
        int wpx = (xpos + Mouse.x - TitleBar.rx);
        int wpy = (ypos + Mouse.y - TitleBar.ry);
        if(wpx > 5 && wpy > 5)
            glfwSetWindowPos(window, wpx, wpy);
    }
    if(TitleBar.dragged && Mouse.button.left.clickup)
    {
        TitleBar.dragged = false;
    }
}