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
                                   vec2uFrom(240, 250), 
                                   vec2uFrom(50, 50), 
                                   colorFromRGB(0, 255, 0), 
                                   colorFromGrayScale(255));
    u16 b = 100;
    int * a = malloc(sizeof(int)*b);
    for(int i = 0; i < b; i++)
    {
        a[i] = i;
    }
    List * list = listCreate(vec2uFrom(10, 10),
                             vec2uFrom(APP_WINDOW_WIDTH-20, APP_WINDOW_HEIGHT-30),
                             colorFromGrayScale(20),
                             colorFromGrayScale(255),
                             (void**)&a, &b,
                             strListObject);

    while(windowIsOpen(window))
    {
        windowNewFrame(window);

        listUpdate(window, list);
        buttonUpdate(window, button);

        renderText("TEVES SOFTWARE", vec2uFrom(0, APP_WINDOW_HEIGHT), 1, colorFromGrayScale(255), TextAlignLeft);
        windowRefresh(window);
    }

    windowDestroy(window);
    shutdownBackend();
    return 0;
}
