#include <GLFW/glfw3.h>
#include <Window/Window.h>
#include <Config.h>
#include <utils/Graphics.h>

void minimizeButtonOnClickCbk(void * window){glfwIconifyWindow(window);}

#include <stdio.h>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

FT_Library ft;
FT_Face face;

void init_freetype() {
    if (FT_Init_FreeType(&ft)) {
        fprintf(stderr, "Could not init FreeType Library\n");
        exit(EXIT_FAILURE);
    }
    if (FT_New_Face(ft, "./arial.ttf", 0, &face)) {
        fprintf(stderr, "Could not open font\n");
        exit(EXIT_FAILURE);
    }
    FT_Set_Pixel_Sizes(face, 0, 512);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            fprintf(stderr, "Could not load character '%c'\n", c);
            continue;
        }

        // Verifica si face->glyph es NULL
        if (face->glyph == NULL) {
            fprintf(stderr, "Glyph is null for character '%c'\n", c);
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

typedef struct char_size
{
    unsigned int w;
    unsigned int h;
}char_size;

char_size render_char(char t, int x, int y, float scale, Color color)
{    
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
    
    colorSetGLColor(color);
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
    char_size out;
    out.h = height;
    out.w = width;
    return out;
}

int main(void)
{       
    //Init GLFW and catch err
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    Window * window = windowCreate(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, "To Do List");

    init_freetype();

    while(windowIsOpen(window))
    {
        windowNewFrame(window);

        int x = 100;
        int y = 100;
        int dx = 0;
        char LETTERS [] = {'A', 'B', 'C', 'D', 'E', 'F'};
        for(int i = 0; i < sizeof(LETTERS); i++)
        {
            dx += render_char(LETTERS[i], x + dx, 100, 1, colorFromRGB(255, 255, 255)).w + 2;
        }

        windowRefresh(window);
    }

    windowDestroy(window);
    glfwTerminate();
    return 0;
}
