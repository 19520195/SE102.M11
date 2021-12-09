#pragma once

#include <d3d9.h>

#include <memory>
#include <unordered_map>
#include "Texture.hh"

class Sprite
{
public:
  Sprite(size_t ID, float top, float left, float bottom, float right, Texture* texture);
  
  RECT* GetRect();
  Texture* GetTexture();

  void Render(float X, float Y); 

private:
  RECT               m_Rect; 
  Texture* m_Texture;
};

class SpriteBase
{
public:
  Sprite* Add(size_t ID, float top, float left, float bottom, float right, Texture* texture);
  Sprite* Get(size_t ID);

  static SpriteBase* GetInstance(); 

private:
  std::unordered_map<size_t, std::shared_ptr<Sprite>> m_Sprites;

private:
  static std::shared_ptr<SpriteBase> s_Instance;
};
