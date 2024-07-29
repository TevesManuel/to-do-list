#ifndef TEVES_WINDOW_INPUT_MOUSE_H
#define TEVES_WINDOW_INPUT_MOUSE_H

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>
#include <Config.h>
#include <utils/Vec2.h>

// typedef struct Vec2u Vec2u;

typedef struct Mouse{
    Vec2u position;
    struct button
    {
        struct left
        {
            bool clicked;
            bool clickup;
            bool clickdown;
        }left;
        struct right
        {
            bool clicked;
            bool clickup;
            bool clickdown;
        }right;
    }button;
}Mouse;

Mouse * mouseCreate();
void mouseButtonUpdate(GLFWwindow * window, Mouse * mouse);
void cursor_position_callback(GLFWwindow* win, double x, double y);
bool mouseIsOverRect(Mouse * mouse, Vec2u rectPosition, Vec2u rectSize);
bool mouseIsOverRadius(Mouse * mouse, Vec2u position, float radius);

#endif