#ifndef SIMPLEGRAPHICS_H
#define SIMPLEGRAPHICS_H
#include <Config.h>

typedef struct Color
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 glow;
}Color;
Color colorFromRGB(u8 r, u8 g, u8 b);
Color colorFromRGBA(u8 r, u8 g, u8 b, u8 a);
void colorSetGLColor(Color color);

void draw_circle(float cx, float cy, float r);
#endif