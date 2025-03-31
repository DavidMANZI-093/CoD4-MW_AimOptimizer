#ifndef AIMCONFIG_H
#define AIMCONFIG_H

#include <opencv2/opencv.hpp>
#include <windows.h>

using namespace cv;

struct AimConfig {
    float smoothing;
    float maxDistance;
    int minAreaSize;
    bool aimAtHead;
    float headOffset;

    Scalar enemyMaskColorLower1;
    Scalar enemyMaskColorUpper1;
    Scalar enemyMaskColorLower2;
    Scalar enemyMaskColorUpper2;

    int exitKey;
    int aimKey;
    int toggleKey;
    int targetFPS;
    bool showDebugWindow;

    AimConfig();  // Constructor
};

#endif // AIMCONFIG_H
