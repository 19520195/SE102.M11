#pragma once
#include "Texture.hh"
#include "IRender2D.hh"

class Sprite : public IRender2D
{
public:
  Sprite(float top, float left, float bottom, float right, Texture* texture);
  
  RECT* GetRect();
  Texture* GetTexture();

  void Render(float X, float Y, TimeStep elapsed = 0); 

private:
  RECT     m_Rect; 
  Texture* m_Texture;
};

class SpriteBase
{
public:
  SpriteBase() = default;
  static Ref<SpriteBase> GetInstance();

  Ref<Sprite> Add(const std::string& name, float top, float left, float bottom, float right, Texture* texture);
  Ref<Sprite> Get(const std::string& name);

private:
  static Ref<SpriteBase> s_Instance;
  HashTable<std::string, Ref<Sprite>> m_Sprites;
};
