#include <Button/Button.h>
#include <math.h>
#include <stdlib.h>
#include <utils/Graphics.h>

Button buttonCreate(int x, int y, int r, struct nk_color color)
{
    Button out;
    out.x = x;
    out.y = y;
    out.r = r;
    out.color = color;
    return out;
}

void buttonRender(Button * button)
{
    int diffx = abs(button->x - Mouse.x);
    int diffy = abs(button->y - Mouse.y);
    int diffxp2 = diffx * diffx;
    int diffyp2 = diffy * diffy;
    int distance = sqrt(diffxp2 + diffyp2);
    float attenuate = 0.5;
    if(distance <= button->r)
    {
        attenuate = 1.0;
        if(Mouse.button.left.clickup)
        {
            if(button->onClickCbk)
            {
                button->onClickCbk(button->onClickCbkArgs);
            }
        }
    }
    glColor3f((button->color.r/255.0)*attenuate, (button->color.g/255.0)*attenuate, (button->color.b/255.0)*attenuate);
    draw_circle(button->x, button->y, button->r);
};