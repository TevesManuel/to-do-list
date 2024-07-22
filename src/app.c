#define APP_WINDOW_WIDTH 640
#define APP_WINDOW_HEIGHT 480

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

bool onExit = false;


static void error_callback(int e, const char *d)
{
    printf("Error %d: %s\n", e, d);
}

void closeButtonOnClickCbk(){onExit = true;};

int main(void)
{   
    //Init GLFW and catch err
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

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

    //Main app
    while (!glfwWindowShouldClose(window) && !onExit)
    {
        glfwPollEvents();
        mouseButtonUpdate(window);
        nk_glfw3_new_frame();

        //Create a nuklear sub window with the main window dimensions
        if (nk_begin(ctx, "Show", nk_rect(0, 0, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT), 0))
        {

            struct nk_color background_color = nk_rgb(255, 255, 255); // Color de fondo deseado
            nk_style_push_color(ctx, &ctx->style.window.fixed_background.data.color, background_color);
            nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT/48, 1);
            nk_label(ctx, "To Do List", NK_TEXT_CENTERED);
            /* Restaura el color original del fondo */
            nk_style_pop_color(ctx);

            nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT/48, 1);
            nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT/24, 1);
            if (nk_button_label(ctx, "Add new task"))
                fprintf(stdout, "button pressed\n");

            nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT/24, 1);
            nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT/24, 1);
            nk_label(ctx, "Tasks:", NK_TEXT_LEFT);

            nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT*0.7, 1);
            if (nk_group_begin(ctx, "", NK_WINDOW_SCROLL_AUTO_HIDE)) {
                // Elementos de la lista
                nk_layout_row_dynamic(ctx, 25, 1);
                for (int i = 0; i < 50; ++i) {
                    nk_label(ctx, "Este es un elemento de la lista", NK_TEXT_LEFT);
                }
                nk_group_end(ctx);
            }

            nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT/24, 1);
            nk_label(ctx, "@Copyright 2024 TEVES", NK_TEXT_LEFT);
            // nk_layout_row_dynamic(ctx, 25, 1);
            // nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

            // nk_layout_row_dynamic(ctx, 25, 1);
            // if (nk_combo_begin_color(ctx, background_color, nk_vec2(nk_widget_width(ctx),400))) {
            //     nk_layout_row_dynamic(ctx, 120, 1);
            //     nk_color_picker(ctx, background_color, NK_RGBA);
            //     nk_layout_row_dynamic(ctx, 25, 1);
            //     // bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
            //     // bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
            //     // bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
            //     // bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
            //     nk_combo_end(ctx);
            // }
        }
        nk_end(ctx);
        
        glViewport(0, 0, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        nk_glfw3_render(NK_ANTI_ALIASING_ON);
        
        //Configure for render OpenGL
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, 0, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

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
