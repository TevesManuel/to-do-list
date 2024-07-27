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

Vec2u renderChar(char t, int x, int y, float scale, Color color)
{    
    if(t == 32)
    {
        Vec2u out;
        out.x = 1.5*scale;
        return out;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Load_Char(face, t, FT_LOAD_RENDER);

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
    unsigned int height = face->glyph->bitmap.rows;
    unsigned int width = face->glyph->bitmap.width;
    width = width * scale * 0.025;
    height = height * scale * 0.025;
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

    glDeleteTextures(1, &texture);
    Vec2u out;
    out.x = height;
    out.y = width;
    return out;
}

#include <string.h>

#define SPACE_BEETWEEN_CHARS 2
#define MAX(a, b) ((a) > (b) ? (a) : (b))

Vec2u renderText(const char * text, Vec2u position, int scale, Color color)
{
    int dx = 0;
    int dy = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        Vec2u d = renderChar(text[i], position.x + dx, position.y, scale, color);
        dx += d.x + SPACE_BEETWEEN_CHARS;
        printf("dx %d c %c\n", dx, text[i]);
        dy = MAX(dy, d.y);
    }
    Vec2u out;
    out.x = dx;
    out.y = dy;
    return out;
}

void draw_circle(float cx, float cy, float r) {
    const int num_segments = 100; // Número de segmentos en el círculo
    float theta = 2.0f * M_PI / (float)num_segments; // Ángulo entre segmentos
    float cos_theta = cosf(theta);
    float sin_theta = sinf(theta);
    float x = r;
    float y = 0.0f;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Centro del círculo

    for (int i = 0; i <= num_segments; ++i) {
        glVertex2f(x + cx, y + cy); // Vértice del círculo

        // Calcular el siguiente vértice
        float temp_x = x;
        x = cos_theta * x - sin_theta * y;
        y = sin_theta * temp_x + cos_theta * y;
    }
    glEnd();
}