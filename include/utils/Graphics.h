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

typedef enum 
{
    Left,
    Center
}Align;

Vec2u renderText(const char * text, Vec2u position, int scale, Color color, Align textAlign);
void renderRect(Vec2u pos, Vec2u size);
void renderRectOutline(Vec2u pos, Vec2u size);
void renderCircle(Vec2u pos, float r);
#endif