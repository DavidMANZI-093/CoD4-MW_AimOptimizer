#include "../configs/AimConfig.h"

// Aim settings
AimConfig::AimConfig()
    : smoothing(5.5f),     // Higher = smoother (slower) movement
      maxDistance(300.0f), // Maximum pixel distance to target
      minAreaSize(50),     // Minimum countour area to consider
      aimAtHead(true),     // Aim at top of bounding box instead of center
      headOffset(0.13f),    // Head position (0 = top, 1= bottom)

      // Color detection ranges (using HSV)
      enemyMaskColorLower1(Scalar(0, 85, 85)), // Lower red range
      enemyMaskColorUpper1(Scalar(5, 185, 185)),
      enemyMaskColorLower2(Scalar(175, 85, 85)), // Upper red range
      enemyMaskColorUpper2(Scalar(180, 185, 185)),

      // Settings key bindings
      aimKey(VK_END), // Key to hold for aiming
      toggleKey('O'), // Key to toggle aim assist
      exitKey('I'),   // Key to exit the program

      // Performance settings
      targetFPS(60),         // Target frames per second
      showDebugWindow(false) // Capture window with overlay
{
}