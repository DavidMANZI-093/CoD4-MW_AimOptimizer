#ifndef CAPTURESCREEN_H
#define CAPTURESCREEN_H

#include <opencv2/opencv.hpp>
#include <dxgi1_2.h>
#include <d3d11.h>

using namespace cv;

Mat CaptureScreen(
    IDXGIOutputDuplication*& l_pDeskDupl,
    ID3D11Device*& l_pDevice,
    ID3D11DeviceContext*& l_pContext,
    const int l_captureWidth,
    const int l_captureHeight,
    const int l_startX,
    const int l_startY
);

#endif