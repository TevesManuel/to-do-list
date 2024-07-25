#ifndef TEVES_WINDOW_H
#define TEVES_WINDOW_H

#include <GLFW/glfw3.h>
#include <Config.h>
#include <Window/Input/Mouse.h>
#include <Window/TitleBar/TitleBar.h>

typedef struct TitleBar TitleBar;

typedef struct Window
{
    bool onExit;
    u8 id;
    GLFWwindow * glfwWindow;
    Mouse * mouse;
    TitleBar * titleBar;
}Window;

Window * windowCreate(u16 width, u16 height, const char * title);
bool windowIsOpen(Window * window);
void windowRefresh(Window * window);
void windowDestroy(Window * window);
void windowNewFrame(Window * window);
#endif