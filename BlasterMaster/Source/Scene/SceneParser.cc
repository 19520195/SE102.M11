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

std::vector<Object*> SceneParser::GetObjects() const
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
    case '#': break;
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

void SceneParser::PrintDebugInfo() const
{
  DEBUG_MSG(L"[TEXTURES]\n");
  for (const auto& detail : m_TextureID)
    DEBUG_MSG(L"%d\t-> %s\n", detail.second, TO_LPWSTR(detail.first));
  DEBUG_MSG(L"[SPRITES]\n");
  for (const auto& detail : m_SpriteID)
    DEBUG_MSG(L"%d\t-> %s\n", detail.second, TO_LPWSTR(detail.first));
  DEBUG_MSG(L"[ANIMATIONS]\n");
  for (const auto& detail : m_AnimationID)
    DEBUG_MSG(L"%d\t-> %s\n", detail.second, TO_LPWSTR(detail.first));
}

Object* SceneParser::ParseObject(const std::string& detail)
{
  std::vector<std::string> tokens = Strings::Split(detail, "\t");
  if (tokens.size() != 5 && tokens.size() != 9)
    return nullptr;

  Object* object = nullptr;
  std::string name = tokens[0];
  if (name == "Brick")
    object = new Brick();
  else if (name == "SophiaIII")
    object = new SophiaIII();
  else object = Enemy::Create(name);
  if (object == nullptr) return nullptr;

  float X = std::stof(tokens[1]);
  float Y = std::stof(tokens[2]);
  float width = std::stof(tokens[3]);
  float height = std::stof(tokens[4]);

  object->SetLocation(X, Y);
  object->SetWidth(width);
  object->SetHeight(height);

  Enemy* enemy = dynamic_cast<Enemy*>(object);
  if (enemy != nullptr)
  {
    if (Trigger* trigger = enemy->CreateTrigger())
      m_Objects.emplace_back(trigger);
  }

  if (name == "SophiaIII")
  {
    m_Player.reset(static_cast<Player*>(object));
    m_Keyboard = m_Player->GetKeyboard();
  }
  else m_Objects.push_back(object);
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

  m_TextureID[name] = ++m_TextureCount;
  return TextureBase::GetInstance()->Add(m_TextureCount, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

Sprite* SceneParser::ParseSprite(const std::string& detail)
{
  std::vector<std::string> tokens = Strings::Split(detail, "\t");
  if (tokens.size() != 6) return nullptr;

  std::string name = tokens[0];
  std::string tname = tokens[1];
  float top = std::stof(tokens[2]);
  float left = std::stof(tokens[3]);
  float bottom = std::stof(tokens[4]);
  float right = std::stof(tokens[5]);

  m_SpriteID[name] = ++m_SpriteCount;
  Texture* texture = TextureBase::GetInstance()->Get(GetTextureID(tname));
  return SpriteBase::GetInstance()->Add(m_SpriteCount, top, left, bottom, right, texture);
}

Animation* SceneParser::ParseAnimation(const std::string& detail)
{
  std::vector<std::string> tokens = Strings::Split(detail, "\t");
  if (tokens.size() < 4) return nullptr;

  std::string name = tokens[0];
  float frameTime = std::stof(tokens[1]);

  Animation* animation = new Animation(frameTime);
  for (size_t i = 2; i < tokens.size(); ++i)
    animation->Add(GetSpriteID(tokens[i]));
  m_AnimationID[name] = ++m_AnimationCount;
  return AnimationBase::GetInstance()->Add(m_AnimationCount, animation);
}
