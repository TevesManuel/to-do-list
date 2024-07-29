#include <Config.h>
#include <Window/Window.h>
#include <stdio.h>
#include <Controls/Button.h>

#include <utils/Graphics.h>
#include <utils/Vec2.h>

void testFn(void * arg)
{
    Window * window = (Window*) arg;
    printf("Test button pressed in window with id %d\n", window->id);
}

int main()
{
    initBackend();
    Window * window = windowCreate(APP_WINDOW_WIDTH,
                                   APP_WINDOW_HEIGHT,
                                   "To Do List", 
                                   colorFromGrayScale(10));
    Button * button = buttonCreate("+",
                                   testFn, 
                                   window, 
                                   vec2uFrom(APP_WINDOW_WIDTH*0.91, APP_WINDOW_HEIGHT*0.88), 
                                   vec2uFrom(50, 50), 
                                   colorFromRGB(0, 255, 0), 
                                   colorFromGrayScale(255));

    while(windowIsOpen(window))
    {
        windowNewFrame(window);

        buttonUpdate(window, button);

        // Definiciones y configuraciones iniciales
        Vec2u position = vec2uFrom(100, 100);
        Vec2u size = vec2uFrom(500, 300);
        Vec2u visiblePosition = vec2uFrom(200, 200);
        Vec2u visibleSize = vec2uFrom(200, 100);
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        renderCircle(visiblePosition, 10, colorFromRGB(255, 0, 255));

        // Configuración del viewport para el recorte
        glViewport(visiblePosition.x, APP_WINDOW_HEIGHT - visiblePosition.y - visibleSize.y, visibleSize.x, visibleSize.y);

        // Configuración de la proyección ortogonal para el recorte
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(visiblePosition.x, visiblePosition.x + visibleSize.x, visiblePosition.y + visibleSize.y, visiblePosition.y, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // Renderizar el rectángulo
        renderRect(position, size, colorFromRGB(255, 0, 0));

        // Restaurar matrices y viewport originales
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        // Renderizar contornos para visualización
        renderRectOutline(position, size, colorFromRGB(0, 255, 0));
        renderRectOutline(visiblePosition, visibleSize, colorFromRGB(0, 255, 255));

        windowRefresh(window);
    }

    windowDestroy(window);
    shutdownBackend();
    return 0;
}
