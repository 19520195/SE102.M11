#include "SceneParser.hh"
#include <fstream>
#include <string>

int SceneParser::GetHeader(const std::string& header)
{
  if (header == "[TEXTURES]" ) return SCENE_HEADER_TEXTURES  ;
  if (header == "[SPRITES]"  ) return SCENE_HEADER_SPRITES   ;
  if (header == "[ANIMATION]") return SCENE_HEADER_ANIMATIONS;
  if (header == "[OBJECTS]"  ) return SCENE_HEADER_OBJECTS   ;
  return SCENE_HEADER_UNKNOW;
}

std::shared_ptr<PlayScene> SceneParser::FromFile(const std::string& filename)
{
  std::ifstream ini(filename);
  if (!ini.is_open()) return nullptr;

  int parsingHeader = SCENE_HEADER_UNKNOW;
  std::shared_ptr<PlayScene> scene(new PlayScene());
  for (std::string buffer; std::getline(ini, buffer); )
  {
    if (buffer.empty()) continue;
    switch (*buffer.begin())
    {
    case '#': break;
    case '[':
      parsingHeader = GetHeader(buffer);
      break; 

    default:
      switch (parsingHeader)
      {
        case SCENE_HEADER_OBJECTS:
          scene->AddObject(ParseObject(buffer));
          break;
        case SCENE_HEADER_TEXTURES:
          ParseTexture(buffer);
          break;
        case SCENE_HEADER_SPRITES:
          ParseSprite(buffer);
          break;
      }
    }
  }

  return scene;
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
  return object;
}

Texture* SceneParser::ParseTexture(const std::string& detail)
{
  std::vector<std::string> args = Split(detail, "\t");
  if (args.size() != 5) return nullptr;

  size_t       ID   = std::stoul(args[0]);
  std::wstring path = std::wstring(args[1].begin(), args[1].end());
  unsigned     R    = std::stoul(args[2]);
  unsigned     G    = std::stoul(args[3]);
  unsigned     B    = std::stoul(args[4]);
  return TextureBase::GetInstance()->Add(ID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

Sprite* SceneParser::ParseSprite(const std::string& detail)
{
  std::vector<std::string> args = Split(detail, "\t");
  if (args.size() != 6) return nullptr;

  size_t ID     = std::stoul(args[0]);
  size_t TID    = std::stoul(args[1]);
  size_t top    = std::stoul(args[2]);
  size_t left   = std::stoul(args[3]);
  size_t bottom = std::stoul(args[4]);
  size_t right  = std::stoul(args[5]);

  Texture* texture = TextureBase::GetInstance()->Get(TID); 
  return SpriteBase::GetInstance()->Add(ID, top, left, bottom, right, texture);
}
