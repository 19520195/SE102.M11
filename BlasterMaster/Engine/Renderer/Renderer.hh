#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Source/BlasterMaster.hh"
#include "Texture.hh"
#include "Sprite.hh"
#include "Animation.hh"

extern LPDIRECT3D9        G_D3D;
extern LPDIRECT3DDEVICE9  G_Device;
extern LPDIRECT3DSURFACE9 G_Buffer;
extern LPD3DXSPRITE       G_SpriteHandler;

class Renderer
{
public:
  static void InitDirectX3D(HWND hWindow, LONG width = 0, LONG height = 0);
  static void CleanDirectX3D();
  static void Render(const TimeStep& elapsed = 0);

  static void DrawSprite(float X, float Y, Sprite* sprite);
};
