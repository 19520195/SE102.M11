#include "SceneParser.hh"
#include "Utility/Strings.hh"
#include <fstream>
#include <string>

SceneParser::SceneParser(const std::string& filename)
{
  m_Filename = filename;
  m_IsParsed = false;
  m_TextureCount = 0;
  m_SpriteCount = 0;
  m_AnimationCount = 0;
}

Ref<Player> SceneParser::GetPlayer() const
{
  return m_Player;
}

std::vector<Ref<Object>> SceneParser::GetObjects() const
{
  return m_Objects;
}

Ref<KeyboardEvent> SceneParser::GetKeyboardEvent() const
{
  return m_Keyboard;
}

size_t SceneParser::GetTextureID(const std::string& name) const
{
  if (m_TextureID.count(name))
    return m_TextureID.at(name);
  return 0;
}

size_t SceneParser::GetSpriteID(const std::string& name) const
{
  if (m_SpriteID.count(name))
    return m_SpriteID.at(name);
  return 0;
}

size_t SceneParser::GetAnimationID(const std::string& name) const
{
  if (m_AnimationID.count(name))
    return m_AnimationID.at(name);
  return 0;
}

int SceneParser::GetHeader(const std::string& header)
{
  if (header == "[TEXTURES]") return SceneHeaderTextures;
  if (header == "[SPRITES]") return SceneHeaderSprites;
  if (header == "[ANIMATIONS]") return SceneHeaderAnimations;
  if (header == "[OBJECTS]") return SceneHeaderObjects;
  return SceneHeaderUnknow;
}

ObjectTag SceneParser::StringToTag(const std::string& str)
{
  if (str == "Brick") return ObjectTag::Brick;
  if (str == "Jason") return ObjectTag::Jason;
  if (str == "SophiaIII") return ObjectTag::SophiaIII;
  if (str == "Scene-Portal") return ObjectTag::ScenePortal;
  return ObjectTag::Undefined;
}

ObjectType SceneParser::TagToType(const ObjectTag& tag)
{
  switch (tag)
  {
  case ObjectTag::Brick:
    return ObjectType::Brick;

  case ObjectTag::SophiaIII:
  case ObjectTag::Jason:
    return ObjectType::Player;

  default:
    return ObjectType::Enemy;
  }
}

bool SceneParser::Parse()
{
  if (m_IsParsed) return false;
  std::ifstream ini(m_Filename);
  if (!ini.is_open()) return false;

  int header = SceneHeaderUnknow;
  for (std::string buffer; std::getline(ini, buffer); )
  {
    if (buffer.empty()) continue;
    switch (*buffer.begin())
    {
    case ';': break;
    case '[':
      header = GetHeader(buffer);
      break;

    default:
      switch (header)
      {
      case SceneHeaderObjects: ParseObject(buffer); break;
      case SceneHeaderTextures: ParseTexture(buffer); break;
      case SceneHeaderSprites: ParseSprite(buffer); break;
      case SceneHeaderAnimations: ParseAnimation(buffer); break;
      }
    }
  }

  m_IsParsed = true;
  return true;
}

Ref<Object> SceneParser::ParseObject(const std::string& detail)
{
  std::vector<std::string> tokens = Strings::Split(detail, "\t");

  Ref<Object> object;
  std::string name = tokens[0];
  auto tag = StringToTag(name);
  switch (tag)
  {
  case ObjectTag::Brick: object = CreateRef<Brick>(); break;
  case ObjectTag::Jason: object = CreateRef<Jason>(); break;
  case ObjectTag::SophiaIII: object = CreateRef<SophiaIII>(); break;
  case ObjectTag::ScenePortal:
    object = CreateRef<ScenePortal>();
    std::static_pointer_cast<ScenePortal>(object)->SetScene(tokens[5]);
    break;
  default: object = Enemy::Create(name);
  }

  // Invalid object
  if (!object)
    return nullptr;

  float X = std::stof(tokens[1]);
  float Y = std::stof(tokens[2]);
  float width = std::stof(tokens[3]);
  float height = std::stof(tokens[4]);

  object->SetLocation(X, Y);
  object->SetWidth(width);
  object->SetHeight(height);

  // Handle single move enemy
  if (Ref<Stuka> stuka = std::dynamic_pointer_cast<Stuka>(object))
    stuka->SetTrail(Y);

  // Handle player
  if (TagToType(tag) == ObjectType::Player)
    m_Keyboard = (m_Player = std::static_pointer_cast<Player>(object))->GetKeyboard();

  m_Objects.push_back(object);
  return object;
}

Texture* SceneParser::ParseTexture(const std::string& detail)
{
  std::vector<std::string> tokens = Strings::Split(detail, "\t");
  if (tokens.size() != 5) return nullptr;

  std::string name = tokens[0];
  std::wstring path = TO_WSTR(tokens[1]);
  unsigned R = std::stoul(tokens[2]);
  unsigned G = std::stoul(tokens[3]);
  unsigned B = std::stoul(tokens[4]);

  return TextureBase::GetInstance()->Add(name, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

Ref<Sprite> SceneParser::ParseSprite(const std::string& detail)
{
  std::vector<std::string> tokens = Strings::Split(detail, "\t");
  if (tokens.size() != 6) return nullptr;

  std::string name = tokens[0];
  std::string srcName = tokens[1];
  float top = std::stof(tokens[2]);
  float left = std::stof(tokens[3]);
  float bottom = std::stof(tokens[4]);
  float right = std::stof(tokens[5]);

  Texture* texture = TextureBase::GetInstance()->Get(srcName);
  return SpriteBase::GetInstance()->Add(name, top, left, bottom, right, texture);
}

Ref<Animation> SceneParser::ParseAnimation(const std::string& detail)
{
  std::vector<std::string> tokens = Strings::Split(detail, "\t");
  if (tokens.size() < 4) return nullptr;

  std::string name = tokens[0];
  float frameTime = std::stof(tokens[1]);

  Ref<Animation> animation = CreateRef<Animation>(frameTime);
  for (size_t i = 2; i < tokens.size(); ++i)
    animation->Add(tokens[i]);
  m_AnimationID[name] = ++m_AnimationCount;
  return AnimationBase::GetInstance()->Add(name, animation);
}
