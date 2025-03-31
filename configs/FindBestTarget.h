#ifndef FINDBESTTARGET
#define FINDBESTTARGET

#include "AimConfig.h"

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Point FindBestTarget(
    const vector<Rect>& enemies,
    AimConfig l_config,
    const int l_startX,
    const int l_startY,
    const int l_captureWidth,
    const int l_captureHeight
);

#endif