#include "../configs/InitDirectX.h"

#include <iostream>

using namespace std;

bool InitDirectX(
    IDXGIOutputDuplication*& l_pDeskDupl,
    ID3D11Device*& l_pDevice,
    ID3D11DeviceContext*& l_pContext
) {
    D3D_FEATURE_LEVEL featureLevel;
    if (
        D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &l_pDevice,
            &featureLevel,
            &l_pContext
        ) != S_OK
    ) {
        cout << " Failed to get D3D11 device" << endl;
        return false;
    }

    IDXGIDevice* pDxgiDevice = nullptr;
    if (
        l_pDevice->QueryInterface(
            __uuidof(IDXGIDevice),
            (void**)&pDxgiDevice
        ) != S_OK || !pDxgiDevice
    ) {
        cout << " Failed to get DXGI device" << endl;
        l_pDevice->Release();
        l_pContext->Release();
        return false;
    }

    IDXGIAdapter* pDxgiAdapter = nullptr;
    if (
        pDxgiDevice->GetParent(
            __uuidof(IDXGIAdapter),
            (void**)&pDxgiAdapter
        ) != S_OK || !pDxgiAdapter
    ) {
        cout << " Failed to get DXGI adapter" << endl;
        pDxgiDevice->Release();
        l_pDevice->Release();
        l_pContext->Release();
        return false;
    }

    IDXGIOutput* pDxgiOutput = nullptr;
    if (
        pDxgiAdapter->EnumOutputs(
            0,
            &pDxgiOutput
        ) != S_OK || !pDxgiOutput
    ) {
        cout << " Failed to enumerate output" << endl;
        pDxgiAdapter->Release();
        pDxgiDevice->Release();
        l_pDevice->Release();
        l_pContext->Release();
        return false;
    }

    IDXGIOutput1* pDxgiOutput1 = nullptr;
    if (
        pDxgiOutput->QueryInterface(
            __uuidof(IDXGIOutput1),
            (void**)&pDxgiOutput1
        ) != S_OK || !pDxgiOutput1
    ) {
        cout << " Failed to get IDXGIOutput1" << endl;
        pDxgiOutput->Release();
        pDxgiAdapter->Release();
        pDxgiDevice->Release();
        l_pDevice->Release();
        l_pContext->Release();
        return false;
    }

    HRESULT hr = pDxgiOutput1->DuplicateOutput(
        l_pDevice,
        &l_pDeskDupl
    );
    if (
        FAILED(hr) || !l_pDeskDupl
    ) {
        cout << " Failed to duplicate output, HRESULT: " << hr << endl;
        pDxgiOutput1->Release();
        pDxgiOutput->Release();
        pDxgiAdapter->Release();
        pDxgiDevice->Release();
        l_pDevice->Release();
        l_pContext->Release();
        return false;
    }

    pDxgiOutput1->Release();
    pDxgiOutput->Release();
    pDxgiAdapter->Release();
    pDxgiDevice->Release();
    return true;
}