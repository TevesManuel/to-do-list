#include <Config.h>

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include <stdbool.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL2_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT

#ifndef NK_SINGLE_FILE
#include <nuklear.h>
#endif
#include <nuklear_gflw.h>

#include <utils/Mouse.h>
#include <Button/Button.h>
#include <TitleBar/TitleBar.h>
#include <utils/Graphics.h>

bool onExit = false;

static void error_callback(int e, const char *d)
{
    printf("Error %d: %s\n", e, d);
}

void closeButtonOnClickCbk(){onExit = true;}
void minimizeButtonOnClickCbk(void * window){glfwIconifyWindow(window);}

int main(void)
{   
    //Init GLFW and catch err
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //Unable title bar
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    //Create error cbk
    glfwSetErrorCallback(error_callback);

    //Create GLFW window & catch err
    GLFWwindow* window = glfwCreateWindow(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, "To do list", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }
    //Create the context of the window
    glfwMakeContextCurrent(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetCursorPosCallback(window, cursor_position_callback);

    //Create the nuklear context
    struct nk_context *ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);

    //Load font
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);
    struct nk_font *font;
    const char *font_path = "./arial.ttf";
    font = nk_font_atlas_add_from_file(atlas, font_path, 20.0f, NULL);
    nk_glfw3_font_stash_end();

    //Initialize the nuklear context
    nk_init_default(ctx, &font->handle);

    //Configure background color
    struct nk_color background_color = nk_rgb(30, 30, 30);
    ctx->style.window.fixed_background = nk_style_item_color(background_color);

    //Center the window in the middle of the screen
    {
        //get videomode of the main monitor
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        int xpos = (mode->width - APP_WINDOW_WIDTH) / 2;
        int ypos = (mode->height - APP_WINDOW_HEIGHT) / 2;

        //Force update the position in any os
        glfwSetWindowPos(window, xpos, ypos);
        glfwShowWindow(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSetWindowPos(window, xpos, ypos);
    }

    Button closeButton = buttonCreate(APP_WINDOW_WIDTH*0.99, 7, 7, nk_rgb(255, 0, 0));
    closeButton.onClickCbk = closeButtonOnClickCbk;
    Button minimizeButton = buttonCreate(APP_WINDOW_WIDTH*0.99 - 18, 7, 7, nk_rgb(180, 180, 180));
    minimizeButton.onClickCbkArgs = window;
    minimizeButton.onClickCbk = minimizeButtonOnClickCbk;

    //Main app
    while (!glfwWindowShouldClose(window) && !onExit)
    {
        glfwPollEvents();
        mouseButtonUpdate(window);
        titleBarUpdate(window);

        //Configure for render OpenGL
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, 0, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        //Configure for opengl
        glViewport(0, 0, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        
        drawMainUI(ctx);

        drawCreate(ctx);


        // Draw circle
        buttonRender(&closeButton);
        buttonRender(&minimizeButton);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    nk_glfw3_shutdown();
    glfwTerminate();
    return 0;
}
