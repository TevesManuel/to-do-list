#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>
#include <stdbool.h>

struct Mouse{
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
};

extern struct Mouse Mouse;

void mouseButtonUpdate(GLFWwindow * window);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

#endif