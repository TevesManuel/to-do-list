#ifndef TEVES_CONTROLS_WINDOWBUTTON_H
#define TEVES_CONTROLS_WINDOWBUTTON_H

#include <Window/Input/Mouse.h>
#include <utils/Graphics.h>
#include <Window/Window.h>
#include <utils/Vec2.h>

typedef struct Window Window;

typedef struct WindowButton
{
    Vec2u position;
    int r;
    Color color;
    void (*onClickCbk)(void*);
    void * onClickCbkArgs;
}WindowButton;

WindowButton * windowButtonCreate(Vec2u position, int r, Color color);
void windowButtonRender(Window * window, WindowButton * button);

#endif