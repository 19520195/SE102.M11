#include "Texture.hh"
#include "Renderer.hh"
#include <Windows.h>

Ref<TextureBase> TextureBase::s_Instance = CreateRef<TextureBase>();
Ref<TextureBase> TextureBase::GetInstance() { return s_Instance; }

TextureBase::~TextureBase()
{
  for (auto& texture : m_Textures)
    if (texture.second != nullptr)
      texture.second->Release();
}


Texture* TextureBase::Add(const std::string& name, LPCWSTR path, D3DCOLOR trans)
{
  D3DXIMAGE_INFO info;
  HRESULT result = D3DXGetImageInfoFromFile(path, &info);
  if (result != D3D_OK)
  {
    OutputDebugString(L"[ERROR] GetImageInfoFromFile failed: %s\n");
    return nullptr;
  }

  LPDIRECT3DDEVICE9 d3ddv = G_Device;
  Texture* texture;

  result = D3DXCreateTextureFromFileEx(
    d3ddv,								// Pointer to Direct3D device object
    path,							    // Path to the image to load
    info.Width,							// Texture width
    info.Height,						// Texture height
    1,
    D3DUSAGE_DYNAMIC,
    D3DFMT_UNKNOWN,
    D3DPOOL_DEFAULT,
    D3DX_DEFAULT,
    D3DX_DEFAULT,
    trans,
    &info,
    NULL,
    &texture);								// Created texture pointer

  if (result != D3D_OK)
  {
    OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
    return nullptr;
  }

  m_Textures[name] = texture;
  return texture;
}

Texture* TextureBase::Get(const std::string& name)
{
  return m_Textures[name];
}

