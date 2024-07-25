SOURCEDIR = ./src
SRC = $(SOURCEDIR)/Window/Input/Mouse.c $(SOURCEDIR)/Window/TitleBar/TitleBar.c  $(SOURCEDIR)/Window/Window.c $(SOURCEDIR)/Button/Button.c $(SOURCEDIR)/utils/Graphics.c $(SOURCEDIR)/app.c
TARGETDIR = ./target
TARGET = $(TARGETDIR)/app.out
CC = gcc
LIBS = -lglfw -lGL -lm -I./include/
default:
	$(CC) $(SRC) -o $(TARGET) $(LIBS)
	$(TARGET)