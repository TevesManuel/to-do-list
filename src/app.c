#include <GLFW/glfw3.h>
#include <Window/Window.h>
#include <Config.h>
#include <utils/Graphics.h>
#include <Controls/Button.h>
#include <stdio.h>

void testFn(void * arg)
{
    Window * window = (Window*) arg;
    printf("Test button pressed in window with id %d\n", window->id);
}

int main()
{       
    //Init GLFW and catch err
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    Window * window = windowCreate(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, "To Do List", colorFromGrayScale(10));
    Button * button = buttonCreate("Touch me", testFn, window, vec2uFrom(100, 100), vec2uFrom(100, 100));
    while(windowIsOpen(window))
    {
        windowNewFrame(window);

        buttonUpdate(button);
        // renderText("Texto de prueba\0", 100, 100, 1.5, colorFromGrayScale(255));

        windowRefresh(window);
    }

    windowDestroy(window);
    glfwTerminate();
    return 0;
}
