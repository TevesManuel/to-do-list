#ifndef TEVES_UTILS_GRAPHICS_H
#define TEVES_UTILS_GRAPHICS_H
#include <utils/Vec2.h>
#include <Config.h>

typedef struct Color
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
    u8 glow;
}Color;
Color colorFromGrayScale(u8 gs);
Color colorFromRGB(u8 r, u8 g, u8 b);
Color colorFromRGBA(u8 r, u8 g, u8 b, u8 a);
void colorSetGLFgColor(Color color);
void colorSetGLBgColor(Color color);

void initGraphics();
Vec2u renderText(const char * text, Vec2u position, int scale, Color color);
void draw_circle(float cx, float cy, float r);
#endif