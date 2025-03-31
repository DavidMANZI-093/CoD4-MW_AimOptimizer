#include "../configs/ProcessInput.h"

#include <iostream>

using namespace std;

//Processing keyboard input
void ProcessInput(
    AimConfig l_config,
    bool* l_isRunning,
    bool* l_aimAssistEnabled,
    high_resolution_clock::time_point* l_lastToggleTime
) {
    // Toggle aim assist on/off
    if (GetAsyncKeyState(l_config.toggleKey) & 1) {
        auto now = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - *l_lastToggleTime).count();

        // Debounce toggle
        if (elapsed > 300) {
            *l_lastToggleTime = now;
            *l_aimAssistEnabled = !*l_aimAssistEnabled;
            cout << " Aim Assist: " << (*l_aimAssistEnabled ? "Enabled" : "Disabled") << endl;
        }
    }

    // Checking exit condition
    if (GetAsyncKeyState(l_config.exitKey) & 1) {
        *l_isRunning = false;
    }
}