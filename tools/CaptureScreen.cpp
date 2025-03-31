#include "../configs/CaptureScreen.h"
#include "../configs/InitDirectX.h"

#include <iostream>

using namespace std;

// Capturing screen with DirectX
Mat CaptureScreen(
    IDXGIOutputDuplication*& l_pDeskDupl,
    ID3D11Device*& l_pDevice,
    ID3D11DeviceContext*& l_pContext,
    const int l_captureWidth,
    const int l_captureHeight,
    const int l_startX,
    const int l_startY
) {
    IDXGIResource* pDesktopResource = nullptr;
    DXGI_OUTDUPL_FRAME_INFO frameInfo;
    ID3D11Texture2D* pAcquiredDesktopImage = nullptr;

    HRESULT hr = l_pDeskDupl->AcquireNextFrame(5, &frameInfo, &pDesktopResource);
    if (FAILED(hr)) {
        if (hr == DXGI_ERROR_ACCESS_LOST) {
            cout << " Access lost, reinitializing DirectX" << endl;

            // Releasing old resources
            if (l_pDeskDupl) {
                l_pDeskDupl->Release();
                l_pDeskDupl = nullptr;
            }

            // Reinitializing
            InitDirectX(l_pDeskDupl, l_pDevice, l_pContext);
        }
        return Mat();
    }

    hr = pDesktopResource->QueryInterface(
        __uuidof(ID3D11Texture2D),
        (void**)&pAcquiredDesktopImage
    );
    pDesktopResource->Release();
    if (FAILED(hr) || !pAcquiredDesktopImage) {
        l_pDeskDupl->ReleaseFrame();
        return Mat();
    }

    D3D11_TEXTURE2D_DESC desc;
    pAcquiredDesktopImage->GetDesc(&desc);

    // Creating staging texture
    ID3D11Texture2D* pStagingTexture = nullptr;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.BindFlags = 0;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.MiscFlags = 0;
    if (
        l_pDevice->CreateTexture2D(
            &desc,
            nullptr,
            &pStagingTexture
        ) != S_OK
    ) {
        pAcquiredDesktopImage->Release();
        l_pDeskDupl->ReleaseFrame();
        return Mat();
    }

    l_pContext->CopyResource(
        pStagingTexture,
        pAcquiredDesktopImage
    );
    pAcquiredDesktopImage->Release();
    l_pDeskDupl->ReleaseFrame();

    //Mapping the staging texture
    D3D11_MAPPED_SUBRESOURCE mapped;
    if (
        l_pContext->Map(
            pStagingTexture,
            0,
            D3D11_MAP_READ,
            0,
            &mapped
        ) != S_OK
    ) {
        pStagingTexture->Release();
        return Mat();
    }

    Mat frame(
        desc.Height,
        desc.Width,
        CV_8UC4,
        mapped.pData,
        mapped.RowPitch
    );
    Mat result = frame.clone(); // Using deep copy to avid data issues after unmmap
    l_pContext->Unmap(pStagingTexture, 0);
    pStagingTexture->Release();

    return result(Rect(
        l_startX,
        l_startY,
        l_captureWidth,
        l_captureHeight
    ));
}