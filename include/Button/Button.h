#ifndef BUTTON_H
#define BUTTON_H

#include <utils/Mouse.h>
#ifndef NK_SINGLE_FILE
#include <nuklear.h>
#endif

typedef struct Button
{
    int x;
    int y;
    int r;
    struct nk_color color;
    void (*onClickCbk)(void);
}Button;

Button buttonCreate(int x, int y, int r, struct nk_color color);
void buttonRender(Button * button);

#endif