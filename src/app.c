#include <Config.h>
#include <Window/Window.h>
#include <stdio.h>
#include <Controls/Button.h>

void testFn(void * arg)
{
    Window * window = (Window*) arg;
    printf("Test button pressed in window with id %d\n", window->id);
}

int main()
{
    initBackend();
    Window * window = windowCreate(APP_WINDOW_WIDTH,
                                   APP_WINDOW_HEIGHT,
                                   "To Do List", 
                                   colorFromGrayScale(10));
    Button * button = buttonCreate("+",
                                   testFn, 
                                   window, 
                                   vec2uFrom(APP_WINDOW_WIDTH*0.91, APP_WINDOW_HEIGHT*0.88), 
                                   vec2uFrom(50, 50), 
                                   colorFromRGB(0, 255, 0), 
                                   colorFromGrayScale(255));

    while(windowIsOpen(window))
    {
        windowNewFrame(window);

        buttonUpdate(window, button);

        windowRefresh(window);
    }

    windowDestroy(window);
    shutdownBackend();
    return 0;
}
