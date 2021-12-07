#pragma once

#include "PlayScene.hh"

enum SceneHeader : int
{
  SCENE_HEADER_UNKNOW    ,
  SCENE_HEADER_TEXTURES  ,
  SCENE_HEADER_SPRITES   ,
  SCENE_HEADER_ANIMATIONS,
  SCENE_HEADER_OBJECTS   ,
};

class SceneParser
{
public:
  static int GetHeader(const std::string& header); 
  static std::shared_ptr<PlayScene> FromFile(const std::string& filename);

  static Object* ParseObjects(const std::string& detail);

private:
};
