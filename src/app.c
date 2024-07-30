#include <Config.h>
#include <Window/Window.h>
#include <stdio.h>
#include <Controls/Button.h>
#include <Controls/List.h>

#include <utils/Graphics.h>
#include <utils/Vec2.h>

void testFn(void * arg)
{
    Window * window = (Window*) arg;
    printf("Test button pressed in window with id %d\n", window->id);
}

char * strListObject(void * listPtr, int index)
{
    int * a = (int*)listPtr;
    char * str = malloc(sizeof(char)*100);
    sprintf(str, "Number: %d", a[index]);
    return str;
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
    u16 b = 100;
    int * a = malloc(sizeof(int)*b);
    for(int i = 0; i < b; i++)
    {
        a[i] = i;
    }
    List * list = listCreate(vec2uFrom(100, 100),
                             vec2uFrom(200, 200),
                             colorFromGrayScale(20),
                             colorFromGrayScale(255),
                             a, &b,
                             strListObject);

    while(windowIsOpen(window))
    {
        windowNewFrame(window);

        buttonUpdate(window, button);
        listUpdate(window, list);
        windowRefresh(window);
    }

    windowDestroy(window);
    shutdownBackend();
    return 0;
}
