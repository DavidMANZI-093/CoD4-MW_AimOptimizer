#include "../configs/InitDirectX.h"

#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

bool InitDirectX(
    IDXGIOutputDuplication*& l_pDeskDupl,
    ID3D11Device*& l_pDevice,
    ID3D11DeviceContext*& l_pContext
) {
    // Local runtime variables
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
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
        cout << " ["
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec
        << "] - Failed to get D3D11 device" << endl;
        return false;
    }

    IDXGIDevice* pDxgiDevice = nullptr;
    if (
        l_pDevice->QueryInterface(
            __uuidof(IDXGIDevice),
            (void**)&pDxgiDevice
        ) != S_OK || !pDxgiDevice
    ) {
        cout << " ["
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec
        << "] - Failed to get DXGI device" << endl;
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
        cout << " ["
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec
        << "] - Failed to get DXGI adapter" << endl;
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
        cout << " ["
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec
        << "] - Failed to enumerate output" << endl;
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
        cout << " ["
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec
        << "] - Failed to get IDXGIOutput1" << endl;
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
        cout << " ["
        << setw(2) << setfill('0') << localTime->tm_hour << ":"
        << setw(2) << setfill('0') << localTime->tm_min << ":"
        << setw(2) << setfill('0') << localTime->tm_sec
        << "] - Failed to duplicate output, HRESULT: " << hr << endl;
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