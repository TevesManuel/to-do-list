SOURCEDIR = ./src
SRC = $(SOURCEDIR)/utils/Mouse.c $(SOURCEDIR)/utils/Graphics.c $(SOURCEDIR)/Button/Button.c $(SOURCEDIR)/TitleBar/TitleBar.c $(SOURCEDIR)/app.c
TARGETDIR = ./target
TARGET = $(TARGETDIR)/app.out
CC = gcc
LIBS = -lglfw -lGL -lm -I./include/
default:
	$(CC) $(SRC) -o $(TARGET) $(LIBS)
	$(TARGET)