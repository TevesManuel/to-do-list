#include <Window/TitleBar/TitleBar.h>
#include <Config.h>
#include <Window/Window.h>

#define TITLE_BG colorFromRGB(30, 30, 30)

static void closeButtonCbk(void * arg)
{
    Window * window = (Window*)arg;
    window->onExit = true;
}

static void minimizeButtonOnClickCbk(void * arg)
{
    Window * window = (Window*)arg;
    glfwIconifyWindow(window->glfwWindow);
}

TitleBar * titleBarCreate(Window * window)
{
    TitleBar * out = (TitleBar*)malloc(sizeof(TitleBar));
    out->rx = 0;
    out->ry = 0;
    out->dragged = false;
    out->color = TITLE_BG;
    out->closeButton = buttonCreate(APP_WINDOW_WIDTH*0.99, 7, 7, colorFromRGB(255, 0, 0));
    out->minimizeButton = buttonCreate(APP_WINDOW_WIDTH*0.99 - 18, 7, 7, colorFromRGB(180, 180, 180));
    out->closeButton->onClickCbk = closeButtonCbk;
    out->closeButton->onClickCbkArgs = (void*)window;
    out->minimizeButton->onClickCbk = minimizeButtonOnClickCbk;
    out->minimizeButton->onClickCbkArgs = (void*)window;
    return out;
}

void titleBarUpdate(Window * window, TitleBar * titleBar)
{
    if(window->mouse->button.left.clickdown && window->mouse->y < APP_WINDOW_HEIGHT*0.05)
    {
        titleBar->dragged = true;
    
        titleBar->rx = window->mouse->x;
        titleBar->ry = window->mouse->y;
    }
    if(titleBar->dragged)
    {
        int xpos, ypos;
        glfwGetWindowPos(window->glfwWindow, &xpos, &ypos);
        int wpx = (xpos + window->mouse->x - titleBar->rx);
        int wpy = (ypos + window->mouse->y - titleBar->ry);
        if(wpx > 5 && wpy > 5)
            glfwSetWindowPos(window->glfwWindow, wpx, wpy);
    }
    if(titleBar->dragged && window->mouse->button.left.clickup)
    {
        titleBar->dragged = false;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTranslatef(0, 0, 0);
    glBegin(GL_QUADS);
        colorSetGLColor(titleBar->color);
        glVertex2i(0, 0);
        glVertex2i(APP_WINDOW_WIDTH, 0);
        glVertex2i(APP_WINDOW_WIDTH, 15);
        glVertex2i(0, 15);
    glEnd();
    glPopMatrix();

    buttonRender(window, titleBar->closeButton);
    buttonRender(window, titleBar->minimizeButton);
}