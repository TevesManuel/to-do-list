#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <stdbool.h>

struct TitleBar
{
    bool dragged;
    double rx;
    double ry;
};

extern struct TitleBar TitleBar;

void titleBarUpdate();

#endif