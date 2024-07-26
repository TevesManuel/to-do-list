#include <GLFW/glfw3.h>
#include <Window/Window.h>
#include <Config.h>
#include <utils/Graphics.h>

#include <stdio.h>

int main()
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

        renderText("Texto de prueba\0", 100, 100, 1.5, colorFromRGB(255, 255, 255));

        windowRefresh(window);
    }

    windowDestroy(window);
    glfwTerminate();
    return 0;
}
