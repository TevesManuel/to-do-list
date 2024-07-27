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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTranslatef(button->pos.x, button->pos.y, 0);
    glBegin(GL_QUADS);
        colorSetGLFgColor(button->bg);
        glVertex2i(0, 0);
        glVertex2i(button->size.x, 0);
        glVertex2i(button->size.x, button->size.y);
        glVertex2i(0, button->size.y);
    glEnd();
    glPopMatrix();
}