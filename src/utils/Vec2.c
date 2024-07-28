#include <utils/Vec2.h>

Vec2u vec2uFrom(u16 x, u16 y)
{
    Vec2u out;
    out.x = x;
    out.y = y;
    return out;
}

Vec2u vec2uAdd(Vec2u a, Vec2u b)
{
    return vec2uFrom(a.x + b.x, a.y + b.y);
}
Vec2u vec2uDiv(Vec2u dividend, u16 divider)
{
    return vec2uFrom(dividend.x / divider, dividend.y / divider);
}