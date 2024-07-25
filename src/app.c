#include <GLFW/glfw3.h>
#include <Window/Window.h>
#include <Config.h>
#include <utils/Graphics.h>

void minimizeButtonOnClickCbk(void * window){glfwIconifyWindow(window);}

#include <stdio.h>

int main(void)
{   
    //Init GLFW and catch err
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    Window * window = windowCreate(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, "To Do List");

    while(windowIsOpen(window))
    {
        windowNewFrame(window);
        
        windowRefresh(window);
    }

    windowDestroy(window);
    glfwTerminate();
    return 0;
}
