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
LIBS = -lglfw -lGL -lm -I./include/ -lfreetype -I/usr/include/freetype2 
default:
	$(CC) $(SRC) -o $(TARGET) $(LIBS)
	$(TARGET)