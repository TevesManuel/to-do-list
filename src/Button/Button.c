#include <Controls/Button.h>
#include <math.h>
#include <stdlib.h>

Button * buttonCreate(int x, int y, int r, Color color)
{
    Button * out = (Button*)malloc(sizeof(Button));
    out->x = x;
    out->y = y;
    out->r = r;
    out->color = color;
    return out;
}

void buttonRender(Window * window, Button * button)
{
    int diffx = abs(button->x - window->mouse->x);
    int diffy = abs(button->y - window->mouse->y);
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
    colorSetGLColor(button->color);
    draw_circle(button->x, button->y, button->r);
};