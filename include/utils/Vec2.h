#ifndef TEVES_UTILS_VEC2
#define TEVES_UTILS_VEC2

#include <Config.h>
typedef struct Vec2u
{
    u16 x;
    u16 y;
}Vec2u;
Vec2u vec2uFrom(u16 x, u16 y);
Vec2u vec2uAdd(Vec2u a, Vec2u b);
Vec2u vec2uDiv(Vec2u dividend, u16 divider);

typedef struct Vec2i
{
    i16 x;
    i16 y;
}Vec2i;
Vec2i vec2iFrom(i16 x, i16 y);
Vec2i vec2iAdd(Vec2u a, Vec2u b);
Vec2i vec2iDiv(Vec2u dividend, i16 divider);
#endif