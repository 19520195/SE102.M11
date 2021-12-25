#pragma once

#include "PlayScene.hh"

enum SceneHeader : int
{
  SceneHeaderUnknow    ,
  SceneHeaderTextures  ,
  SceneHeaderSprites   ,
  SceneHeaderAnimations,
  SceneHeaderObjects   ,
};

class SceneParser
{
public:
  SceneParser() = delete;
  SceneParser(const std::string& filename);

  Object*               GetPlayer() const;
  std::vector<Object*>  GetObjects() const;
  Ref<KeyboardEvent>    GetKeyboardEvent() const;

  size_t GetTextureID(const std::string& name) const;
  size_t GetSpriteID(const std::string& name) const;
  size_t GetAnimationID(const std::string& name) const;

  int GetHeader(const std::string& header);

  bool Parse();
  void PrintDebugInfo() const;

  Object*    ParseObject(const std::string& detail);
  Texture*   ParseTexture(const std::string& detail); 
  Sprite*    ParseSprite(const std::string& detail);
  Animation* ParseAnimation(const std::string& detail);

private:
  std::string m_Filename;
  bool        m_IsParsed;

  Player*              m_Player;
  Ref<KeyboardEvent>   m_Keyboard;
  std::vector<Object*> m_Objects; 

  size_t m_TextureCount;
  size_t m_SpriteCount;
  size_t m_AnimationCount;
  std::unordered_map<std::string, size_t> m_TextureID;
  std::unordered_map<std::string, size_t> m_SpriteID;
  std::unordered_map<std::string, size_t> m_AnimationID;
};
