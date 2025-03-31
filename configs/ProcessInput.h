#ifndef PROCESSINPUT_H
#define PROCESSINPUT_H

#include "./AimConfig.h"

#include <windows.h>
#include <chrono>

using namespace std::chrono;

void ProcessInput(
    AimConfig l_config,
    bool* l_isRunning,
    bool* l_aimAssistEnabled,
    high_resolution_clock::time_point* l_lastToggleTime
);

#endif