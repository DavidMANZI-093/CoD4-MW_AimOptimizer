#ifndef INITDIRECTX_H
#define INITDIRECTX_H

#include <d3d11.h>
#include <dxgi1_2.h>

bool InitDirectX(
    IDXGIOutputDuplication*& l_pDeskDupl,
    ID3D11Device*& l_pDevice,
    ID3D11DeviceContext*& l_pContext
);

#endif