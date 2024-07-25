#ifndef BUTTON_H
#define BUTTON_H

#include <Window/Input/Mouse.h>
#include <utils/Graphics.h>
#include <Window/Window.h>

typedef struct Window Window;

typedef struct Button
{
    int x;
    int y;
    int r;
    Color color;
    void (*onClickCbk)(void*);
    void * onClickCbkArgs;
}Button;

Button * buttonCreate(int x, int y, int r, Color color);
void buttonRender(Window * window, Button * button);

#endif