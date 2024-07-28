#include <Controls/Button.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <utils/Graphics.h>

Button * buttonCreate(const char * label, void (*onClick)(void*), void * argFn, Vec2u pos, Vec2u size)
{
    Button * out = (Button*) malloc(sizeof(Button));
    out->label = label;
    out->onClickFn = onClick;
    out->onClickFnArg = argFn;
    out->pos = pos;
    out->size = size;
    out->bg = colorFromGrayScale(200);
    return out;
}

void buttonUpdate(Button * button)
{
    colorSetGLFgColor(button->bg);
    renderRect(button->pos, button->size);
}