SOURCEDIR = ./src
SRC = $(SOURCEDIR)/utils/Mouse.c $(SOURCEDIR)/utils/simpleGraphics.c $(SOURCEDIR)/Button/Button.c $(SOURCEDIR)/app.c
TARGETDIR = ./target
TARGET = $(TARGETDIR)/app.out
CC = gcc
LIBS = -lglfw -lGL -lm -I./include/
default:
	$(CC) $(SRC) -o $(TARGET) $(LIBS)
	$(TARGET)