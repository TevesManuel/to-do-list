#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Mouse{
    int x;
    int y;
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

#endif