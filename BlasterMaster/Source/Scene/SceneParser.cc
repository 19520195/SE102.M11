#include "SceneParser.hh"
#include <fstream>
#include <string>

SceneParser::SceneParser(const std::string& filename)
{
  m_Filename = filename;
  m_IsParsed = false;
  m_TextureCount   = 0;
  m_SpriteCount    = 0;
  m_AnimationCount = 0;
}

std::vector<Object*> SceneParser::GetObjects() const
{
  return m_Objects;
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
  if (header == "[TEXTURES]"  ) return SceneHeaderTextures  ;
  if (header == "[SPRITES]"   ) return SceneHeaderSprites   ;
  if (header == "[ANIMATIONS]") return SceneHeaderAnimations;
  if (header == "[OBJECTS]"   ) return SceneHeaderObjects   ;
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
        case SceneHeaderObjects   : ParseObject(buffer)   ; break;
        case SceneHeaderTextures  : ParseTexture(buffer)  ; break;
        case SceneHeaderSprites   : ParseSprite(buffer)   ; break;
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
    DEBUG_MSG(L"%d\t-> %s\n", detail.second, TO_LPSTR(detail.first));
  DEBUG_MSG(L"[SPRITES]\n");
  for (const auto& detail : m_SpriteID)
    DEBUG_MSG(L"%d\t-> %s\n", detail.second, TO_LPSTR(detail.first));
  DEBUG_MSG(L"[ANIMATIONS]\n");
  for (const auto& detail : m_AnimationID)
    DEBUG_MSG(L"%d\t-> %s\n", detail.second, TO_LPSTR(detail.first));
}

std::vector<std::string> Split(std::string string, std::string delimeter)
{
  std::vector<std::string> tokens;
  size_t last = 0; size_t next = 0;
  for (; (next = string.find(delimeter, last)) != std::string::npos; last = next + 1)
    tokens.emplace_back(string.substr(last, next - last));
  tokens.emplace_back(string.substr(last));
  return tokens;
}

Object* SceneParser::ParseObject(const std::string& detail)
{
  std::vector<std::string> tokens = Split(detail, "\t");
  if (tokens.size() < 5) return nullptr;

  size_t ID      = std::stoul(tokens[0]);
  float  X       = std::stof (tokens[1]);
  float  Y       = std::stof (tokens[2]);
  float  width   = std::stof (tokens[3]);
  float  height  = std::stof (tokens[4]);

  Object* object; 
  switch (ID)
  {
  case OBJECT_ID_BRICK:
    object = new Brick();
    break;

  default:
    return nullptr; 
  }

  object->SetXY(X, Y); 
  object->SetWidth(width);
  object->SetHeight(height);
  m_Objects.push_back(object);
  return object;
}

Texture* SceneParser::ParseTexture(const std::string& detail)
{
  std::vector<std::string> args = Split(detail, "\t");
  if (args.size() != 5) return nullptr;

  std::string  name = args[0];
  std::wstring path = std::wstring(args[1].begin(), args[1].end());
  unsigned     R    = std::stoul(args[2]);
  unsigned     G    = std::stoul(args[3]);
  unsigned     B    = std::stoul(args[4]);

  m_TextureID[name] = ++m_TextureCount;
  return TextureBase::GetInstance()->Add(m_TextureCount, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

Sprite* SceneParser::ParseSprite(const std::string& detail)
{
  std::vector<std::string> args = Split(detail, "\t");
  if (args.size() != 6) return nullptr;

  std::string name   = args[0];
  std::string tname  = args[1];
  size_t      top    = std::stoul(args[2]);
  size_t      left   = std::stoul(args[3]);
  size_t      bottom = std::stoul(args[4]);
  size_t      right  = std::stoul(args[5]);

  m_SpriteID[name] = ++m_SpriteCount;
  Texture* texture = TextureBase::GetInstance()->Get(GetTextureID(tname));
  return SpriteBase::GetInstance()->Add(m_SpriteCount, top, left, bottom, right, texture);
}

Animation* SceneParser::ParseAnimation(const std::string& detail)
{
  std::vector<std::string> args = Split(detail, "\t");
  if (args.size() < 4) return nullptr;

  std::string name      = args[0];
  size_t      frameTime = std::stoul(args[1]);

  Animation* animation = new Animation(frameTime); 
  for (size_t i = 2; i < args.size(); ++i)
    animation->Add(GetSpriteID(args[i]));
  m_AnimationID[name] = ++m_AnimationCount;
  return AnimationBase::GetInstance()->Add(m_AnimationCount, animation);
}
