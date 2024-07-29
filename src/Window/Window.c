#include <Window/Window.h>
#include <stdio.h>
#include <utils/Graphics.h>

static void error_callback(int e, const char *d)
{
    printf("Error %d: %s\n", e, d);
}

u8 id = 1;

Window * windowCreate(u16 width, u16 height, const char * title, Color bg)
{
    Window * out = (Window*)malloc(sizeof(Window));
    out->bg = bg;
    out->onExit = false;
    out->id = id;
    id++;
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(-1);
    }
    out->glfwWindow = window;
    glfwSetWindowUserPointer(window, out);

    glfwMakeContextCurrent(window);
    initGraphics();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwMakeContextCurrent(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Center the window in the middle of the screen
    {
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

    Mouse * mouse = mouseCreate();
    out->mouse = mouse;

    glfwSetCursorPosCallback(window, cursor_position_callback);

    out->titleBar = titleBarCreate(out);
    out->titleBar->title = title;

    return out;
}

bool windowIsOpen(Window * window)
{
    return !glfwWindowShouldClose(window->glfwWindow) && !window->onExit;
}

void windowRefresh(Window * window)
{
    titleBarUpdate(window, window->titleBar);
    glfwSwapBuffers(window->glfwWindow);
}

void windowDestroy(Window * window)
{
    glfwDestroyWindow(window->glfwWindow);
    free(window->mouse);
    free(window);
}

void windowNewFrame(Window * window)
{
    glfwPollEvents();
    mouseButtonUpdate(window->glfwWindow, window->mouse);

    //Configure for render OpenGL
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Configure for opengl
    glViewport(0, 0, APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT);
    colorSetGLBgColor(window->bg);
    glClear(GL_COLOR_BUFFER_BIT);
}