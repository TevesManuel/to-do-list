#ifndef TEVES_WINDOW_TITLEBAR_H
#define TEVES_WINDOW_TITLEBAR_H
#define TEVES_WINDOW_TITLEBAR_HEIGHT 15
#include <stdbool.h>
#include <utils/Graphics.h>
#include <Controls/WindowButton.h>

typedef struct WindowButton WindowButton;
typedef struct Window Window;

typedef struct TitleBar
{
    bool dragged;
    double rx;
    double ry;
    Color color;
    WindowButton * closeButton;
    WindowButton * minimizeButton;
    const char * title;
}TitleBar;

TitleBar * titleBarCreate(Window * window);
void titleBarUpdate();

#endif