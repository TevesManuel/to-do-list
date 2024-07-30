#ifndef TEVES_CONTROLS_LIST
#define TEVES_CONTROLS_LIST

#include <Window/Window.h>
#include <utils/Vec2.h>

typedef struct List
{
    Vec2u position;
    Vec2u size;
    Vec2i textPosition;
    Color bg;
    Color fg;
    void ** listItems;
    u16 * sizeOfList;
    char * (*strObjectFn)(void*, int);
}List;

List * listCreate(Vec2u position, Vec2u size, Color bg, Color fg, void ** listItems, u16 * sizeOfList, char* (*strObjectFn)(void*, int));
void listUpdate(Window * window, List * list);

#endif