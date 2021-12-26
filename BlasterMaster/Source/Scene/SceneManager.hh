#pragma once
#include "PlayScene.hh"
#include <fstream>
#include <string>
#include <unordered_map>

enum SceneManagerHeader : uint32_t
{
  SMH_FFFF,
  SMH_Scenes,
  SMH_Configs,
};

enum SceneManagerConfig : uint32_t
{
  SMC_FFFF,
  SMC_Start,
};

class SceneInfo
{
public:
  SceneInfo() = default;
  SceneInfo(const std::string& rFile, const std::string& oFile);
  Ref<Scene> Get() const;

private:
  std::string m_RFile; // Resources
  std::string m_OFile; // Objects
};

class SceneManager
{
public:
  SceneManager() = default;
  static Ref<SceneManager> GetInstance();

  bool LoadConfig(const std::string& filename);
  Ref<Scene> Get(const std::string& name) const;
  Ref<Scene> GetCurrentScene() const;

private:
  uint32_t StringToHeader(const std::string& str);
  uint32_t StringToConfig(const std::string& str);

  bool ParseScene(const std::string& str);
  bool ParseConfig(const std::string& str);

  std::string m_StartScene;
  std::string m_CurrentScene;
  std::unordered_map<std::string, SceneInfo> m_Scenes;

  static Ref<SceneManager> s_Instance;
};
