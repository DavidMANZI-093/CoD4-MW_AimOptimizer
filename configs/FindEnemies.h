#ifndef FINDENEMIES_H
#define FINDENEMIES_H

#include "AimConfig.h"

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

vector<Rect> FindEnemies(
    const Mat& l_frame,
    AimConfig l_config
);

#endif