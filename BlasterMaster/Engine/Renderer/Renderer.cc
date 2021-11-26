#include "Source/BlasterMaster.hh"
#include "Renderer.hh"
#include "Texture.hh"
#include "Animation.hh"

#include "Engine/Core/Game.hh"

LPDIRECT3D9        G_D3D = NULL;
LPDIRECT3DDEVICE9  G_Device = NULL;
LPDIRECT3DSURFACE9 G_Buffer = NULL;
LPD3DXSPRITE       G_SpriteHandler = NULL;

void Renderer::InitDirectX3D(HWND hWindow, LONG width, LONG height)
{
  G_D3D = Direct3DCreate9(D3D_SDK_VERSION);

  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory(&d3dpp, sizeof(d3dpp));

  d3dpp.Windowed = TRUE;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
  d3dpp.BackBufferCount = 1;

  d3dpp.BackBufferWidth = width;
  d3dpp.BackBufferHeight = height;

  G_D3D->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    hWindow,
    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
    &d3dpp,
    &G_Device);

  if (G_Device == NULL)
  {
    OutputDebugString(L"[ERROR] CreateDevice failed\n");
    return;
  }

  G_Device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &G_Buffer);

  // Initialize sprite helper from Direct3DX helper library
  D3DXCreateSprite(G_Device, &G_SpriteHandler);

  OutputDebugString(L"[INFO] InitGame done;\n");
}

void Renderer::CleanDirectX3D()
{
  if (G_D3D != NULL) G_D3D->Release();
  if (G_Device != NULL) G_Device->Release();
  if (G_Buffer != NULL) G_Buffer->Release();
  if (G_SpriteHandler != NULL) G_SpriteHandler->Release();
}

void Renderer::Render()
{
  if (G_Device->BeginScene() == S_OK)
  {
    G_Device->ColorFill(G_Buffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
    G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

    // Render objects
    // Renderer::Draw(-1344-128*(R_SophiaIII.GetX()-16 * 4), -48 - 128*(R_SophiaIII.GetY()- (16 * 8 - 4)), SpriteBase::GetInstance()->Get(20001));
    R_SophiaIII.Render();

    G_SpriteHandler->End();
    G_Device->EndScene();
  }

  // Display back buffer content to the screen
  G_Device->Present(NULL, NULL, NULL, NULL);
}

void Renderer::Draw(float X, float Y, Sprite* sprite)
{
  // Reformat coordiante 
  Y += SCREEN_HEIGHT - (sprite->GetRect()->bottom - sprite->GetRect()->top + 1);
  
  // Drawing sprite
  D3DXVECTOR3 p(round(X), round(Y), 0);
  G_SpriteHandler->Draw(
    sprite->GetTexture(), 
    sprite->GetRect(),
    NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}
