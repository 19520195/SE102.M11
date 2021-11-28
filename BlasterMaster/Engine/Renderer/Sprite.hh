#pragma once

#include <d3d9.h>

#include <memory>
#include <unordered_map>

class Sprite
{
public:
  Sprite(size_t ID, size_t top, size_t left, size_t bottom, size_t right, LPDIRECT3DTEXTURE9 texture);
  
  RECT* GetRect();
  LPDIRECT3DTEXTURE9 GetTexture();

  void Render(float X, float Y); 

private:
  size_t m_ID;
  size_t m_Top;
  size_t m_Left;
  size_t m_Bottom;
  size_t m_Right;

  RECT               m_Rect; 
  LPDIRECT3DTEXTURE9 m_Texture;
};

class SpriteBase
{
public:
  void Add(size_t ID, size_t top, size_t left, size_t bottom, size_t right, LPDIRECT3DTEXTURE9 texture);
  Sprite* Get(size_t ID);

  static SpriteBase* GetInstance(); 

private:
  std::unordered_map<size_t, std::shared_ptr<Sprite>> m_Sprites;

private:
  static std::shared_ptr<SpriteBase> s_Instance;
};
