#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <stdbool.h>
#include <utils/Graphics.h>
#include <Controls/Button.h>

typedef struct Button Button;
typedef struct Window Window;

typedef struct TitleBar
{
    bool dragged;
    double rx;
    double ry;
    Color color;
    Button * closeButton;
    Button * minimizeButton;
}TitleBar;

TitleBar * titleBarCreate(Window * window);
void titleBarUpdate();

#endif