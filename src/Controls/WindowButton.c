#include <Controls/WindowButton.h>
#include <stdlib.h>

WindowButton * windowButtonCreate(Vec2u position, int r, Color color)
{
    WindowButton * out = (WindowButton*)malloc(sizeof(WindowButton));
    out->position = position;
    out->r = r;
    out->color = color;
    return out;
}

void windowButtonRender(Window * window, WindowButton * button)
{
    button->color.glow = 128;
    if(mouseIsOverRadius(window->mouse, button->position, button->r))
    {
        button->color.glow = 255;
        if(window->mouse->button.left.clickup)
        {
            if(button->onClickCbk)
            {
                button->onClickCbk(button->onClickCbkArgs);
            }
        }
    }
    colorSetGLFgColor(button->color);
    renderCircle(button->position, button->r, button->color);
};