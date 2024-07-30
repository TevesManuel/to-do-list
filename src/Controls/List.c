#include<Controls/List.h>

List * listCreate(Vec2u position, Vec2u size, Color bg, Color fg, void * listItems, u16 * sizeOfList, char* (*strObjectFn)(void*, int))
{
    List * out = (List*)malloc(sizeof(List));
    out->position = position;
    out->size = size;
    out->textPosition = vec2uFrom(0, 0);
    out->bg = bg;
    out->fg = fg;
    out->listItems = listItems;
    out->sizeOfList = sizeOfList;
    out->strObjectFn = strObjectFn;
    return out;
}

float antScroll = 0.0f;

void listUpdate(Window * window, List * list)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    glViewport(list->position.x, APP_WINDOW_HEIGHT - list->position.y - list->size.y, list->size.x, list->size.y);

    // Configuration of the proyection orthogonal for the cutout
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(list->position.x, list->position.x + list->size.x, list->position.y + list->size.y, list->position.y, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    list->textPosition.y += window->mouse->scroll.offset * 10;

    // All works good
    // renderRect(vec2uFrom(list->position.x + 10, list->position.y + 10), vec2uFrom(list->size.x - 20, list->size.y - 20), colorFromRGB(255, 255, 255));
    renderRect(list->position, list->size, list->bg);

    for(int i = 0; i < *list->sizeOfList; i++)
    {
        char * text = list->strObjectFn(list->listItems, i);
        renderText(text, 
                   vec2uFrom(list->position.x, list->position.y + i * 15 + list->textPosition.y),
                   1,
                   list->fg,
                   Left);
        free(text);
        renderCircle(list->position, 10, colorFromRGB(0, 255, 0));
    }

    // Restore arrays & viewport originals
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

    // Render outline for debug
    renderRectOutline(list->position, list->size, colorFromRGB(0, 255, 255));
}