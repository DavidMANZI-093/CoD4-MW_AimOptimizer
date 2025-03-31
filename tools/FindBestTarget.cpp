#include "../configs/FindBestTarget.h"

#include <windows.h>

// Finding the best target from detected enemies
Point FindBestTarget(
    const vector<Rect>& enemies,
    AimConfig l_config,
    const int l_startX,
    const int l_startY,
    const int l_captureWidth,
    const int l_captureHeight
) {
    if (enemies.empty()) {
        return Point(-1, 1);
    }

    // Getting current mouse position relative to captured area
    POINT mousePos;
    GetCursorPos(&mousePos);
    mousePos.x -= l_startX;
    mousePos.y -= l_startY;

    // Calculating screen center
    Point center(
        l_captureWidth / 2,
        l_captureHeight / 2
    );

    // Finding closest enemy to center/cursor
    Rect bestEnemy = enemies[0];
    float bestDistance = FLT_MAX;

    for (const auto& enemy : enemies) {
        // Calculating target position (set to center or head)
        Point targetPos;
        if (l_config.aimAtHead) {
            // Aiming at head
            targetPos.x = enemy.x + enemy.width / 2;
            targetPos.y = enemy.y + int(enemy.height * l_config.headOffset);
        } else {
            // Aiming at center
            targetPos.x = enemy.x + enemy.width / 2;
            targetPos.y = enemy.y + enemy.height / 2;
        }

        // Calculating distance from mouse
        float distance = norm(targetPos - Point(mousePos.x, mousePos.y));

        // If this enemy is closer than my current best and within max distance
        if (distance < bestDistance && distance < l_config.maxDistance) {
            bestDistance = distance;
            bestEnemy = enemy;
        }
    }

    // If I found a valid target, return its position
    if (bestDistance < l_config.maxDistance) {
        if (l_config.aimAtHead) {
            return Point(
                bestEnemy.x + bestEnemy.width / 2,
                bestEnemy.y + int(bestEnemy.height * l_config.headOffset)
            );
        } else {
            return Point(
                bestEnemy.x + bestEnemy.width / 2,
                bestEnemy.y + bestEnemy.height / 2
            );
        }
    }

    return Point(-1, -1);
}