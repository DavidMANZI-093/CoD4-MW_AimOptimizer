#include <d3d11.h>
#include <dxgi1_2.h>
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

#include "./configs/AimConfig.h"
#include "./configs/InitDirectX.h"
#include "./configs/CaptureScreen.h"
#include "./configs/FindEnemies.h"
#include "./configs/FindBestTarget.h"
#include "./configs/MoveMouse.h"
#include "./configs/ProcessInput.h"

using namespace cv;
using namespace std;
using namespace std::chrono;

// Setting DirectX globals
IDXGIOutputDuplication* g_pDeskDupl = nullptr;
ID3D11Device* g_pDevice = nullptr;
ID3D11DeviceContext* g_pContext = nullptr;

// Defining Screen settings
const int screenWidth = 1366, screenHeight = 768;
const int captureWidth = 683, captureHeight = 384;
const int startX = (screenWidth - captureWidth) / 2;
const int startY = (screenHeight - captureHeight) / 2;

// Aim settings
AimConfig config;

// Runtime variables
bool g_isRunning = true;
bool g_aimAssistEnabled = true;
std::mutex g_mtx;
high_resolution_clock::time_point g_lastFireTime;
high_resolution_clock::time_point g_lastToggleTime;

// Entry point
int main() {
    // Local runtime variables
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    cout << " CoD4 MW Aim Optimizer - Research/Debug Tool" << endl;
    cout << " ----------------------------------------" << endl;
    cout << "  - O: Toggle Aim Assist" << endl;
    cout << "  - END: Activate Aim" << endl;
    cout << "  - I: Exit Program" << endl;
    cout << " ----------------------------------------" << endl;
    
    // Seeding random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    
    if (!InitDirectX(g_pDeskDupl, g_pDevice, g_pContext)) {
        cout << " ["
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec
        << "] - DirectX Initialization Failed!" << endl;
        return -1;
    }
    
    // Initializing timing variables
    g_lastToggleTime = high_resolution_clock::now();
    g_lastFireTime = high_resolution_clock::now();
    
    // Setting FPS calculation variables
    int frameCount = 0;
    auto fpsStartTime = high_resolution_clock::now();
    
    namedWindow("CoD4 MW - AimOptimizer", WINDOW_NORMAL);
    resizeWindow("CoD4 MW - AimOptimizer", captureWidth, captureHeight);
    
    while (g_isRunning) {
        auto frameStartTime = high_resolution_clock::now();
        
        // Processing keyboard input
        ProcessInput(
            config,
            &g_isRunning,
            &g_aimAssistEnabled,
            &g_lastToggleTime
        );
        
        // Capturing screen
        Mat frame = CaptureScreen(
            g_pDeskDupl,
            g_pDevice,
            g_pContext,
            captureWidth,
            captureHeight,
            startX,
            startY
        );
        if (frame.empty()) {
            cout << " ["
            << setw(2) << setfill('0') << localTime->tm_hour << ":"
            << setw(2) << setfill('0') << localTime->tm_min << ":"
            << setw(2) << setfill('0') << localTime->tm_sec
            << "] - Failed to capture frame" << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        
        // Creating debug frame if showing debug window
        Mat debugFrame;
        if (config.showDebugWindow) {
            debugFrame = frame.clone();
        }
        
        if (g_aimAssistEnabled) {
            // Finding enemies
            vector<Rect> enemies = FindEnemies(frame, config);
            
            // Drawing debug info
            if (config.showDebugWindow && !enemies.empty()) {
                for (const auto& enemy : enemies) {
                    rectangle(debugFrame, enemy, Scalar(0, 255, 0), 2);
                    
                    // Drawing aim point
                    Point aimPoint;
                    if (config.aimAtHead) {
                        aimPoint = Point(enemy.x + enemy.width / 2, 
                                      enemy.y + int(enemy.height * config.headOffset));
                    } else {
                        aimPoint = Point(enemy.x + enemy.width / 2, 
                                      enemy.y + enemy.height / 2);
                    }
                    circle(debugFrame, aimPoint, 3, Scalar(0, 0, 255), -1);
                }
            }
            
            // Finding best target and aim if key is pressed
            if (GetAsyncKeyState(config.aimKey) & 0x8000) {
                Point targetPos = FindBestTarget(
                    enemies,
                    config,
                    startX,
                    startY,
                    captureWidth,
                    captureHeight
                );
                if (targetPos.x != -1) {
                    MoveMouse(
                        targetPos,
                        config,
                        startX,
                        startY
                    );
                    
                    // Drawing aiming line in debug view
                    if (config.showDebugWindow) {
                        POINT mousePos;
                        GetCursorPos(&mousePos);
                        mousePos.x -= startX;
                        mousePos.y -= startY;
                        
                        if (mousePos.x >= 0 && mousePos.x < captureWidth && 
                            mousePos.y >= 0 && mousePos.y < captureHeight) {
                            line(debugFrame, Point(mousePos.x, mousePos.y), targetPos, 
                                 Scalar(255, 0, 0), 1, LINE_AA);
                        }
                    }
                }
            }
        }
        
        // Showing debug window
        if (config.showDebugWindow) {
            // Adding status text
            string statusText = g_aimAssistEnabled ? " Aim Assist: ON" : " Aim Assist: OFF";
            putText(debugFrame, statusText, Point(10, 30), 
                    FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            
            // Calculating and displaying FPS
            frameCount++;
            auto now = high_resolution_clock::now();
            auto elapsed = duration_cast<milliseconds>(now - fpsStartTime).count();
            
            if (elapsed > 1000) {
                float fps = frameCount * 1000.0f / elapsed;
                string fpsText = "FPS: " + to_string(int(fps));
                fpsStartTime = now;
                frameCount = 0;
                
                putText(debugFrame, fpsText, Point(10, 60), 
                        FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
            }
            
            imshow("CoD4 MW - AimOptimizer", debugFrame);
        }

        // Processing window events
        int key = waitKey(1);
        if (key == 'Q') {
            g_isRunning = false;
        }
        
        // Limiting FPS to target
        auto frameEndTime = high_resolution_clock::now();
        auto frameDuration = duration_cast<milliseconds>(frameEndTime - frameStartTime).count();
        int sleepTime = std::max(0, int(1000 / config.targetFPS - frameDuration));
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
    }
    
    // Cleanup
    if (g_pDeskDupl) g_pDeskDupl->Release();
    if (g_pContext) g_pContext->Release();
    if (g_pDevice) g_pDevice->Release();
    destroyAllWindows();
    
    cout << " ["
    << setw(2) << setfill('0') << localTime->tm_hour << ":"
    << setw(2) << setfill('0') << localTime->tm_min << ":"
    << setw(2) << setfill('0') << localTime->tm_sec
    << "] - Program terminated." << endl;
    return 0;
}