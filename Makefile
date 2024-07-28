SOURCEDIR = ./src
SRC += $(SOURCEDIR)/utils/Graphics.c 
SRC += $(SOURCEDIR)/utils/Vec2.c
SRC += $(SOURCEDIR)/Window/Input/Mouse.c 
SRC += $(SOURCEDIR)/Window/TitleBar/TitleBar.c
SRC += $(SOURCEDIR)/Window/Window.c
SRC += $(SOURCEDIR)/Controls/WindowButton.c
SRC += $(SOURCEDIR)/Controls/Button.c
SRC += $(SOURCEDIR)/app.c
TARGETDIR = ./target
TARGET = $(TARGETDIR)/app.out
CC = gcc
CFLAGS = -I./include/ -I/usr/include/freetype2 
LIBS = -lglfw -lGL -lm -lfreetype 

WINDOWS_CC = x86_64-w64-mingw32-gcc
WINDOWS_CFLAGS = -Wall -I./include/ -I/usr/x86_64-w64-mingw32/include
WINDOWS_LIBS = -lgdi32 -lglfw3 -lopengl32 -lm

default:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)
	$(TARGET)
debug:
	$(CC) $(SRC) -o $(TARGET) $(LIBS) -DTEVES_DEBUG
	$(TARGET)
windows_export:
	$(WINDOWS_CC) $(SRC) -o $(TARGETDIR)/app.exe $(WINDOWS_CFLAGS) $(WINDOWS_LIBS)