#include "../configs/FindEnemies.h"

// Finding enemies using HSV color detection with customized filtering
vector<Rect> FindEnemies(
    const Mat& l_frame,
    AimConfig l_config
) {
    Mat hsv;
    cvtColor(
        l_frame,
        hsv,
        COLOR_BGR2HSV
    );

    // Decting enemies by color range (red in my case)
    Mat mask1, mask2, mask;
    inRange(
        hsv,
        l_config.enemyMaskColorLower1,
        l_config.enemyMaskColorUpper1,
        mask1
    );
    inRange(
        hsv,
        l_config.enemyMaskColorLower2,
        l_config.enemyMaskColorUpper2,
        mask2
    );
    mask = mask1 | mask2;

    // Applying morphological operations to reduce noise
    Mat kernel = getStructuringElement(
        MORPH_RECT,
        Size(3, 3)
    );
    morphologyEx(
        mask,
        mask,
        MORPH_OPEN,
        kernel
    );
    morphologyEx(
        mask,
        mask,
        MORPH_CLOSE,
        kernel
    );

    // Finding contours
    vector<vector<Point>> contours;
    findContours(
        mask,
        contours,
        RETR_EXTERNAL,
        CHAIN_APPROX_SIMPLE
    );

    // Filtering and sorting contours by area (largest first)
    vector<Rect> enemyRects;
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area > l_config.minAreaSize) {
            Rect rect = boundingRect(contour);
            enemyRects.push_back(rect);
        }
    }

    // Sorting by area (largest first)
    sort(
        enemyRects.begin(),
        enemyRects.end(),
        [](const Rect& a, const Rect& b) {
            return a.area() > b.area();
        }
    );

    return enemyRects;
}