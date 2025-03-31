# CoD4 MW Aim Optimizer - Research/Debug Tool

## Description

This tool is designed for research and debugging purposes in *Call of Duty 4: Modern Warfare*. It captures the game screen in real-time, detects enemy players based on their color (red by default), and provides aim assistance by moving the mouse cursor towards detected targets. The tool is intended for educational use, such as studying game mechanics, computer vision techniques, or debugging, and not for cheating in actual gameplay.

## Features

- **Real-time Screen Capture**: Uses DirectX 11 to capture a portion of the game screen.
- **Enemy Detection**: Identifies enemies using HSV color-based segmentation (default: red).
- **Aim Assistance**: Moves the mouse cursor towards the closest target with customizable smoothing.
- **Toggleable Functionality**: Enable or disable aim assist with a key press.
- **Debug Visualization**: Optional window to display captured frames with enemy bounding boxes and aim points.
- **Configurable Settings**: Adjust detection and aiming behavior via code parameters.

## Usage

1. Compile and run the executable on a Windows system.
2. Use the following default key bindings:
   - **'O'**: Toggle aim assist on or off.
   - **'END'**: Hold to activate aim assistance (moves the mouse to the target).
   - **'I'**: Exit the program.
3. Optionally, enable the debug window by setting `showDebugWindow` to `true` in the code to visualize enemy detection.

**Note**: If the default keys ('O', 'END', 'I') conflict with in-game controls, you can modify `aimKey`, `toggleKey`, and the exit condition in the code (e.g., change `P` or `'I'` in the `AimConfig` struct or `main` function).

## Configuration

The tool includes configurable parameters in the `AimConfig` struct, adjustable in the code:

- **`smoothing`**: Controls mouse movement speed (default: 2.5; higher = smoother but slower).
- **`maxDistance`**: Maximum distance in pixels to consider a target (default: 300).
- **`minAreaSize`**: Minimum contour area to detect as an enemy (default: 50).
- **`aimAtHead`**: Toggle aiming at the head (true) or center (false) of the enemy (default: true).
- **`headOffset`**: Adjusts the head aim point (0 = top, 1 = bottom; default: 0.2).
- **`enemyMaskColorLower1/Upper1` & `Lower2/Upper2`**: HSV ranges for enemy color detection (default: two red ranges).
- **`targetFPS`**: Target frames per second (default: 60).
- **`showDebugWindow`**: Enable/disable the debug window (default: false).

Modify these in the code to suit your research needs or game environment.

## How It Works

### Screen Capture
The tool uses DirectX 11 to capture a centered 683x384 pixel region from a 1366x768 screen. Adjust `screenWidth`, `screenHeight`, `captureWidth`, and `captureHeight` in the code if your resolution differs.

### Enemy Detection
Enemies are detected by converting the captured frame to HSV color space and applying two red color masks (adjustable via `enemyMaskColor` settings). Contours are filtered by area (`minAreaSize`) to reduce noise, and the largest valid contours are considered enemies.

### Aim Assistance
When the aim key is held, the tool:
1. Finds the closest enemy to the mouse cursor within `maxDistance`.
2. Calculates the target position (head or center based on `aimAtHead` and `headOffset`).
3. Smoothly moves the mouse using `smoothing` to mimic human-like motion.

### Debug Mode
Set `showDebugWindow` to `true` to display the captured frame with green bounding boxes around detected enemies, red aim points, and a blue line showing the aiming path.

## Performance and Permissions

- **DirectX**: Requires administrative privileges on some systems for screen capture.
- **Performance**: Screen capture and processing may be CPU-intensive. Adjust `targetFPS` to balance performance.
- **Game Mode**: Run *Call of Duty 4* in windowed or borderless fullscreen mode for best results.

## Platform

This tool is Windows-only, relying on DirectX 11 and the Windows API for screen capture and input handling.

## Dependencies

- **OpenCV**: For image processing and computer vision (e.g., `opencv2/opencv.hpp`).
- **DirectX 11**: For screen capture (e.g., `d3d11.h`, `dxgi1_2.h`).
- **Windows API**: For mouse/keyboard input (e.g., `windows.h`).

Install these libraries and link them during compilation.

## Build Instructions

1. Install OpenCV and configure your compiler with its include/library paths.
2. Install the Windows SDK for DirectX and Windows API support.
3. Compile the C++ code with a compatible compiler (e.g., Visual Studio).
4. Link against required libraries: `d3d11.lib`, `dxgi.lib`, and OpenCV libraries (e.g., `opencv_world.lib`).

## Disclaimer

This tool is strictly for research and educational purposes. It is not intended for use in live gameplay to gain an unfair advantage. The author does not endorse cheating in video games and provides this code solely for learning, debugging, or exploring computer vision and game mechanics.