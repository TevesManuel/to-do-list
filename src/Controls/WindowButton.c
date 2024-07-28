#include <Controls/WindowButton.h>
#include <math.h>
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
    int diffx = abs(button->position.x - window->mouse->position.x);
    int diffy = abs(button->position.y - window->mouse->position.y);
    int diffxp2 = diffx * diffx;
    int diffyp2 = diffy * diffy;
    int distance = sqrt(diffxp2 + diffyp2);
    button->color.glow = 128;
    if(distance <= button->r)
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
    renderCircle(button->position, button->r);
};