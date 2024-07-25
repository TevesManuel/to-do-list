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

Color colorFromRGBA(u8 r, u8 g, u8 b, u8 a)
{
    Color out;
    out.r = r;
    out.g = g;
    out.b = b;
    out.a = a;
    out.glow = 255;
    return out;
}

void colorSetGLColor(Color color)
{
    glColor4f((color.r/color.glow)/255.0f, (color.g/color.glow)/255.0f, (color.b/color.glow)/255.0f, color.a/255.0f); // Color negro con 50% de transparencia
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