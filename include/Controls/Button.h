#ifndef TEVES_CONTROLS_BUTTON_H
#define TEVES_CONTROLS_BUTTON_H

#include <utils/Vec2.h>
#include <utils/Graphics.h>

typedef struct Button
{
    const char * label;
    void (*onClickFn)(void*);
    void * onClickFnArg;
    Vec2u pos;
    Vec2u size;
    Color bg;
    Color fg;
}Button;

Button * buttonCreate(const char * label, void (*onClick)(void*), void * argFn, Vec2u pos, Vec2u size);
void buttonUpdate(Button * button);

#endif