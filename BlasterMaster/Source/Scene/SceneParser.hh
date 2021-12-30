#pragma once

#include "PlayScene.hh"

enum SceneHeader : int
{
  SceneHeaderUnknow,
  SceneHeaderTextures,
  SceneHeaderSprites,
  SceneHeaderAnimations,
  SceneHeaderObjects,
  SceneHeaderConfigs,
};

enum class ObjectTag : uint32_t
{
  Undefined,
  Brick,
  Jason,
  SophiaIII,
  ScenePortal
};

enum class ObjectType : uint32_t
{
  Brick,
  Player,
  Enemy,
  Portal,
};

class SceneParser
{
public:
  SceneParser() = delete;
  SceneParser(const std::string& filename);

  Ref<Player>              GetPlayer() const;
  std::vector<Ref<Object>> GetObjects() const;
  Ref<KeyboardEvent>       GetKeyboardEvent() const;

  float GetScreenWidth() const;
  float GetScreenHeight() const;

  size_t GetTextureID(const std::string& name) const;
  size_t GetSpriteID(const std::string& name) const;
  size_t GetAnimationID(const std::string& name) const;

  int GetHeader(const std::string& header);
  ObjectTag StringToTag(const std::string& str);
  ObjectType TagToType(const ObjectTag& tag);

  bool Parse();

  Ref<Object>     ParseObject(const std::string& detail);
  Texture* ParseTexture(const std::string& detail);
  Ref<Sprite>     ParseSprite(const std::string& detail);
  Ref<Animation>  ParseAnimation(const std::string& detail);
  void            ParseConfiguaration(const std::string& str);

private:
  std::string m_Filename;
  bool        m_IsParsed;

  Ref<Player>              m_Player;
  Ref<KeyboardEvent>       m_Keyboard;
  std::vector<Ref<Object>> m_Objects;

  float m_ScreenWidth;
  float m_ScreenHeight;

  size_t m_TextureCount;
  size_t m_SpriteCount;
  size_t m_AnimationCount;

  std::unordered_map<std::string, size_t> m_TextureID;
  std::unordered_map<std::string, size_t> m_SpriteID;
  std::unordered_map<std::string, size_t> m_AnimationID;
};
