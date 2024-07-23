#include <GLFW/glfw3.h>
#include <math.h>

#ifndef M_PI//For vscode no error
#define M_PI 3.1415926
#endif

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

#ifndef NK_SINGLE_FILE
#include <nuklear.h>
#endif
#include <nuklear_gflw.h>

#include <Config.h>
#include <stdio.h>
#include <stdbool.h>

bool boolean_value;

void drawMainUI(struct nk_context *ctx )
{
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
            for (int i = 0; i < 1; ++i) {
                nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT/24, 2);
                struct nk_rect bounds = nk_widget_bounds(ctx);
                bounds.w = 20;
                bounds.h = 20;
                
                if (nk_input_is_mouse_click_down_in_rect(&ctx->input, NK_BUTTON_LEFT, bounds, nk_true)) {
                    boolean_value = !boolean_value;
                }
                
                struct nk_color color = boolean_value ? nk_rgb(0, 255, 0) : nk_rgb(255, 0, 0);
                nk_fill_circle(nk_window_get_canvas(ctx), bounds, color);
                nk_label(ctx, "Este es un elemento de la lista", NK_TEXT_LEFT);
            }
            nk_group_end(ctx);
        }

        nk_layout_row_dynamic(ctx, APP_WINDOW_HEIGHT/24, 1);
        nk_label(ctx, "@Copyright 2024 TEVES", NK_TEXT_LEFT);
    }
    nk_end(ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}

struct nk_colorf bg;

void drawCreate(struct nk_context *ctx)
{
    if (boolean_value)
    {
        // Dibujar cuadrado semitransparente
        glBegin(GL_QUADS);
            glColor4f(0.0f, 0.0f, 0.0f, 0.5f); // Color negro con 50% de transparencia
            glVertex2i(0, 0);
            glVertex2i(APP_WINDOW_WIDTH, 0);
            glVertex2i(APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
            glVertex2i(0, APP_WINDOW_HEIGHT);
        glEnd();

        nk_glfw3_new_frame();

        if (nk_begin(ctx, "Create todo", nk_rect(APP_WINDOW_WIDTH * 0.25, APP_WINDOW_HEIGHT * 0.25, APP_WINDOW_WIDTH * 0.5, APP_WINDOW_HEIGHT * 0.5), NK_WINDOW_BORDER | NK_WINDOW_TITLE))
        {
            nk_layout_row_dynamic(ctx, 20, 1);
            if (nk_button_label(ctx, "Cerrar Ventana"))
            {
                boolean_value = !boolean_value;
                printf("Hi\n");
            }
            nk_end(ctx);
        }

        nk_glfw3_render(NK_ANTI_ALIASING_ON);
    }
}