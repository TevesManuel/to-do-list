#include <Controls/Button.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <utils/Graphics.h>

Button * buttonCreate(const char * label, void (*onClick)(void*), void * argFn, Vec2u pos, Vec2u size, Color bg, Color fg)
{
    Button * out = (Button*) malloc(sizeof(Button));
    out->label = label;
    out->onClickFn = onClick;
    out->onClickFnArg = argFn;
    out->position = pos;
    out->size = size;
    out->bg = bg;
    out->fg = fg;
    return out;
}

void buttonUpdate(Window * window, Button * button)
{
    button->bg.glow = 128;
    if(mouseIsOverRect(window->mouse, button->position, button->size))
    {
        button->bg.glow = 255;
        if(window->mouse->button.left.clickup)
        {
            if(button->onClickFn)
            {
                button->onClickFn(button->onClickFnArg);
            }
        }
    }
    renderRect(button->position, button->size, button->bg);
    renderText(button->label, vec2uAdd(button->position, vec2uDiv(button->size, 2)), 1, button->fg, Center);
}