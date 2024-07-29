#include <utils/Graphics.h>
#include <GLFW/glfw3.h>
#include <math.h>

#ifndef M_PI//For vscode no error
#define M_PI 3.1415926
#endif

Color colorFromRGB(u8 r, u8 g, u8 b)
{
    Color out;
    out.r = r;
    out.g = g;
    out.b = b;
    out.a = 255;
    out.glow = 255;
    return out;
}

Color colorFromGrayScale(u8 gs)
{
    return colorFromRGB(gs, gs, gs);
}

Color colorFromRGBA(u8 r, u8 g, u8 b, u8 a)
{
    Color out = colorFromRGB(r, g, b);
    out.a = a;
    return out;
}

void colorSetGLFgColor(Color color)
{
    glColor4f((color.r*color.glow/255.0f)/255.0f, (color.g*color.glow/255.0f)/255.0f, (color.b*color.glow/255.0f)/255.0f, color.a/255.0f);
}
void colorSetGLBgColor(Color color)
{
    glClearColor((color.r*color.glow/255.0f)/255.0f, (color.g*color.glow/255.0f)/255.0f, (color.b*color.glow/255.0f)/255.0f, color.a/255.0f);
}
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

FT_Library ft;
FT_Face face;
#include <stdio.h>

void initGraphics() {
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init FreeType Library\n");
        exit(EXIT_FAILURE);
    }
    if (FT_New_Face(ft, "./arial.ttf", 0, &face)) {
        fprintf(stderr, "Could not open font\n");
        exit(EXIT_FAILURE);
    }
    FT_Set_Pixel_Sizes(face, 0, 512);
}

#include <utils/Vec2.h>

#define CHAR_PRESCALE 0.025
#define SPACE_BEETWEEN_CHARS 2

Vec2u sizeChar(char c, float scale)
{
    if(c == 32)
    {
        Vec2u out;
        out.x = 5*scale;
        out.y = 1*scale;
        return out;
    }
    FT_Load_Char(face, c, FT_LOAD_RENDER);
    u16 height = face->glyph->bitmap.rows;
    u16 width = face->glyph->bitmap.width;
    width = width * scale * CHAR_PRESCALE;
    height = height * scale * CHAR_PRESCALE;
    return vec2uFrom(width, height);
}

Vec2u sizeText(const char * text, float scale)
{
    Vec2u d;
    Vec2u out = vec2uFrom(0, 0);
    for(u16 i = 0; i < strlen(text); i++)
    {
        d = sizeChar(text[i], scale);
        out.x += d.x + SPACE_BEETWEEN_CHARS;
        out.y = MAX(out.y, d.y);
    }
    return out;
}

Vec2u renderChar(char c, u16 x, u16 y, float scale, Color color)
{    
    if(c == 32)
    {
        Vec2u out;
        out.x = 5*scale;
        out.y = 1*scale;
        return out;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Load_Char(face, c, FT_LOAD_RENDER);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, face->glyph->bitmap.width,
        face->glyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer);
    
    colorSetGLFgColor(color);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTranslatef(x, y, 0);
    u16 height = face->glyph->bitmap.rows;
    u16 width = face->glyph->bitmap.width;
    width = width * scale * CHAR_PRESCALE;
    height = height * scale * CHAR_PRESCALE;
    glBegin(GL_QUADS);
    
        glTexCoord2i(0, 0);
        glVertex2i(0, -height);

        glTexCoord2i(1, 0);
        glVertex2i(width, -height);

        glTexCoord2i(1, 1);
        glVertex2i(width, 0);

        glTexCoord2i(0, 1);
        glVertex2i(0, 0);

    glEnd();
    glPopMatrix();

    // printf("C: \"%c\", X: %d, Y: %d, W: %d, H: %d\n", c, x, y, width, height);

    glDeleteTextures(1, &texture);
    Vec2u out;
    out.x = width;
    out.y = height;
    #ifdef TEVES_DEBUG_CHAR
    colorSetGLFgColor(colorFromRGB(0, 255, 0));
    renderRectOutline(vec2uFrom(x, y), out);
    #endif
    return out;
}

#include <string.h>


Vec2u renderText(const char * text, Vec2u position, int scale, Color color, Align textAlign)
{
    Vec2u renderPosition = position;
    if(textAlign == Center)
    {
        renderPosition.x = position.x - (sizeText(text, scale).x/2.0);
    }
    int dx = 0;
    int dy = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        Vec2u d = renderChar(text[i], renderPosition.x + dx, renderPosition.y, scale, color);

        dx += d.x + SPACE_BEETWEEN_CHARS;
        dy = MAX(dy, d.y);
    }
    Vec2u out;
    out.x = dx;
    out.y = dy;
    #ifdef TEVES_DEBUG
    colorSetGLFgColor(colorFromRGB(0, 255, 0));
    renderCircle(position, 4);
    renderRectOutline(renderPosition, out);
    #endif
    return out;
}

void renderRect(Vec2u pos, Vec2u size, Color color)
{
    colorSetGLFgColor(color);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(pos.x, pos.y, 0);
    glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(size.x, 0);
        glVertex2i(size.x, size.y);
        glVertex2i(0, size.y);
    glEnd();
    glPopMatrix();
}

void renderRectOutline(Vec2u pos, Vec2u size, Color color)
{
    colorSetGLFgColor(color);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(pos.x, pos.y, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(0, 0); 
        glVertex2i(size.x, 0);
        glVertex2i(size.x, size.y);
        glVertex2i(0, size.y);
    glEnd();
    glPopMatrix();
}

void renderCircle(Vec2u pos, float r, Color color) {
    colorSetGLFgColor(color);
    const int num_segments = 100;
    float theta = 2.0f * M_PI / (float)num_segments;
    float cos_theta = cosf(theta);
    float sin_theta = sinf(theta);
    float x = r;
    float y = 0.0f;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(pos.x, pos.y, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);

    for (int i = 0; i <= num_segments; ++i) {
        glVertex2f(x, y);

        float temp_x = x;
        x = cos_theta * x - sin_theta * y;
        y = sin_theta * temp_x + cos_theta * y;
    }
    glEnd();
    glPopMatrix();
}