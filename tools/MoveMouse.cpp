#include "../configs/MoveMouse.h"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// Moving cursor with smoothed, human-like motion
void MoveMouse(
    const Point& targetPos,
    AimConfig l_config,
    const int l_startX,
    const int l_startY
) {
    // Local runtime variables
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    if (targetPos.x < 0 || targetPos.y < 0) {
        return; // Invalid target
    }

    // Getting current mouse position
    POINT currentPos;
    GetCursorPos(&currentPos);

    // Calculating the distance to move
    float dx = (targetPos.x + l_startX) - currentPos.x;
    float dy = (targetPos.y + l_startY) - currentPos.y;

    // Applying smoothing factor
    dx /= l_config.smoothing;
    dy /= l_config.smoothing;

    // Applying integer rounding to ensure consistent movement
    int intDx = (int)(dx + (dx >= 0 ? 0.5f : -0.5f));
    int intDy = (int)(dy + (dy >= 0 ? 0.5f : -0.5f));

    // Adding slight random variation for more human-like movement
    // dx += ((rand() % 100) / 100.0f - 0.5f) * 2.0f;
    // dy += ((rand() % 100) / 100.0f - 0.5f) * 2.0f;

    // Target Coordinates
    cout << " ["
    << setw(2) << setfill('0') << localTime->tm_hour << ":"
    << setw(2) << setfill('0') << localTime->tm_min << ":"
    << setw(2) << setfill('0') << localTime->tm_sec
    << "] - Possible target at [x(" << intDx << "), y(" << intDy << ")]" << endl;

    // Moving the mouse
    SetCursorPos(
        currentPos.x + intDx,
        currentPos.y + intDy
    );
}