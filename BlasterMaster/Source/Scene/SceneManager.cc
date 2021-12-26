#include "SceneManager.hh"
#include "Utility/Strings.hh"

Ref<SceneManager> SceneManager::s_Instance = CreateRef<SceneManager>();
Ref<SceneManager> SceneManager::GetInstance()
{
  return s_Instance;
}

bool SceneManager::LoadConfig(const std::string& filename)
{
  m_Scenes.clear();
  std::ifstream cfgFile(filename);
  if (!cfgFile.is_open())
    return false;

  uint32_t header = SMH_FFFF;
  for (std::string buffer; std::getline(cfgFile, buffer); )
  {
    if (buffer.empty()) continue;
    switch (*buffer.begin())
    {
    case ';': break;
    case '[':
      header = StringToHeader(buffer);
      break;

    default:
      switch (header)
      {
        case SMH_Scenes: ParseScene(buffer); break;
        case SMH_Configs: ParseConfig(buffer); break;
      }
    }
  }

  return true;
}

Ref<Scene> SceneManager::Get(const std::string& name) const
{
  if (m_Scenes.count(name))
    return m_Scenes.at(name).Get();
  return nullptr;
}

Ref<Scene> SceneManager::GetCurrentScene() const
{
  return this->Get(m_CurrentScene);
}

uint32_t SceneManager::StringToHeader(const std::string& str)
{
  if (str == "[SCENES]") return SMH_Scenes;
  if (str == "[CONFIGS]") return SMH_Configs;
  return SMH_FFFF;
}

uint32_t SceneManager::StringToConfig(const std::string& str)
{
  if (str == "START") return SMC_Start;
  return SMC_FFFF;
}

bool SceneManager::ParseScene(const std::string& str)
{
  auto tokens = Strings::Split(str, "\t");
  if (tokens.size() != 3)
    return false;

  std::string name = tokens[0];
  std::string rFile = tokens[1];
  std::string oFile = tokens[2];
  m_Scenes[name] = SceneInfo(rFile, oFile);
  return true;
}

bool SceneManager::ParseConfig(const std::string& str)
{
  auto tokens = Strings::Split(str, "=");
  if (tokens.size() != 2) 
    return false;

  uint32_t cfg = StringToConfig(tokens[0]);
  std::string desc = tokens[1];

  switch (cfg)
  {
  case SMC_Start:
    m_StartScene = desc;
    m_CurrentScene = desc;
    break;

  default:
    return false;
  }

  return true;
}

SceneInfo::SceneInfo(const std::string& rFile, const std::string& oFile)
  : m_RFile(rFile), m_OFile(oFile)
{
}

Ref<Scene> SceneInfo::Get() const
{
  return CreateRef<PlayScene>(m_RFile, m_OFile);
}
