#include "../configs/ProcessInput.h"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

//Processing keyboard input
void ProcessInput(
    AimConfig l_config,
    bool* l_isRunning,
    bool* l_aimAssistEnabled,
    high_resolution_clock::time_point* l_lastToggleTime
) {
    // Local runtime variables
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    // Toggle aim assist on/off
    if (GetAsyncKeyState(l_config.toggleKey) & 1) {
        auto now = high_resolution_clock::now();
        auto elapsed = duration_cast<milliseconds>(now - *l_lastToggleTime).count();

        // Debounce toggle
        if (elapsed > 300) {
            *l_lastToggleTime = now;
            *l_aimAssistEnabled = !*l_aimAssistEnabled;
            cout << " ["
            << setw(2) << setfill('0') << localTime->tm_hour << ":"
            << setw(2) << setfill('0') << localTime->tm_min << ":"
            << setw(2) << setfill('0') << localTime->tm_sec
            << "] - Aim Assist: " << (*l_aimAssistEnabled ? "Enabled" : "Disabled") << endl;
        }
    }

    // Checking exit condition
    if (GetAsyncKeyState(l_config.exitKey) & 1) {
        *l_isRunning = false;
    }
}