# **CoD4 MW Aim Optimizer - Research/Debug Tool**

## **Description**

This tool is designed for research and debugging purposes in **Call of Duty 4: Modern Warfare**. It utilizes computer vision techniques (powered by **OpenCV**) to detect enemies based on their color (red by default) and provides aim assistance by moving the mouse cursor towards detected enemies. The tool includes configurable settings and an optional debug window for visualization.

---

## **Features**

- **Real-time Screen Capture**: Captures a portion of the game screen using **DirectX 11**.
- **Enemy Detection**: Identifies enemies using **HSV color-based segmentation** (default: red).
- **Aim Assistance**: Moves the mouse cursor towards the closest target with customizable smoothing for natural movement.
- **Toggleable Functionality**: Enable or disable aim assistance with a key press.
- **Debug Visualization**: Displays captured frames with bounding boxes and aim points for debugging.
- **Configurable Settings**: Adjust detection and aiming behavior via code parameters.

---

## **Usage**

1. **Compile and Run**:
   - Compile the code using a compatible Windows compiler (e.g., Visual Studio).
   - Run the executable on a Windows system.

2. **Default Key Bindings**:
   - **`O`**: Toggle aim assist on or off.
   - **`END`**: Hold to activate aim assistance (moves the mouse to the target).
   - **`I`**: Exit the program.

3. **Optional Debug Mode**:
   - Enable the debug window by setting `showDebugWindow` to `true` in the code. This will visualize enemy detection with bounding boxes and aim points.

**Note**: If the default keys (`O`, `END`, `I`) conflict with in-game controls, you can modify the key bindings in the code. Refer to the `AimConfig` struct for customization.

---

## **Configuration**

The tool provides various adjustable parameters in the `AimConfig` struct to fine-tune its behavior:

- **`smoothing`**: Controls the speed of mouse movement (default: `2.5`).
- **`maxDistance`**: Maximum distance (in pixels) for target detection (default: `300`).
- **`minAreaSize`**: Minimum contour area to detect as an enemy (default: `50`).
- **`aimAtHead`**: Toggle aiming at the head (`true`) or center (`false`) of the enemy (default: `true`).
- **`headOffset`**: Adjust the head aim point (0 = top, 1 = bottom; default: `0.2`).
- **`enemyMaskColorLower1/Upper1`** & **`Lower2/Upper2`**: HSV ranges for enemy color detection (default: two red ranges).
- **`targetFPS`**: Target frames per second (default: `60`).
- **`showDebugWindow`**: Enable/disable the debug window (default: `false`).

Modify these parameters in the code to suit your research needs or game environment.

---

## **How It Works**

### **1. Screen Capture**
The tool captures a centered 683x384 pixel region from a 1366x768 screen using **DirectX 11**. These dimensions can be adjusted via the following variables:
   - `screenWidth`
   - `screenHeight`
   - `captureWidth`
   - `captureHeight`

### **2. Enemy Detection**
- Converts captured frames to **HSV color space**.
- Applies two red color masks (adjustable via `enemyMaskColor` settings).
- Filters detected contours by area (`minAreaSize`) to identify enemies.

### **3. Aim Assistance**
When the aim key is held:
1. Finds the closest enemy to the mouse cursor within `maxDistance`.
2. Calculates the target position (head or center based on `aimAtHead` and `headOffset`).
3. Smoothly moves the mouse towards the target using the `smoothing` parameter.

### **4. Debug Mode**
If `showDebugWindow` is enabled, the tool displays the captured frame:
- **Green bounding boxes**: Detected enemies.
- **Red aim points**: Target points on enemies.
- **Blue line**: Aiming path visualization.

---

## **Performance and System Requirements**

- **Platform**: Windows-only, relying on **DirectX 11** and the **Windows API**.
- **Performance**: CPU-intensive for real-time screen capture and processing. Adjust `targetFPS` to balance performance.
- **Permissions**: May require administrative privileges for screen capture.
- **Game Mode**: Run the game in windowed or borderless fullscreen mode for better results.

---

## **Dependencies**

The project depends on the following libraries:

1. **OpenCV**:
   - Provides image processing and computer vision capabilities.
   - Required headers: `opencv2/opencv.hpp`.

2. **DirectX 11**:
   - Handles screen capture functionality.
   - Required headers: `d3d11.h`, `dxgi1_2.h`.

3. **Windows API**:
   - Manages mouse and keyboard input.
   - Required headers: `windows.h`.

Ensure these libraries are installed and linked during compilation.

---

## **Build Instructions**

1. **Install Dependencies**:
   - Download and configure **OpenCV** with your compiler.
   - Install the **Windows SDK** for DirectX and Windows API support.

2. **Configure Compiler**:
   - Include necessary library paths for **OpenCV** and **DirectX**.
   - Link against the following libraries:
     - `d3d11.lib`
     - `dxgi.lib`
     - OpenCV libraries (e.g., `opencv_world.lib`).

3. **Build the Project**:
   - Use a compatible compiler (e.g., Visual Studio) to compile the project and generate the executable.

---

## **Disclaimer**

This tool is strictly for **research and educational purposes**. It is not intended for use in live gameplay to gain an unfair advantage. The author does not endorse cheating in video games and provides this tool solely for learning and experimentation.
