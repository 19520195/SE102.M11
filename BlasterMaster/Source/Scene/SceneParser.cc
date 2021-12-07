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
        scene->AddObject(ParseObjects(buffer));
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

Object* SceneParser::ParseObjects(const std::string& detail)
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
