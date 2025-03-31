#ifndef MOVEMOUSE_H
#define MOVEMOUSE_H

#include "AimConfig.h"

#include <windows.h>

using namespace std;

void MoveMouse(
    const Point& targetPos,
    AimConfig l_config,
    const int l_startX,
    const int l_startY
);

#endif