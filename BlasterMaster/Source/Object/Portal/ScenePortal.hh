#pragma once
#include "Portal.hh"

class ScenePortal : public Portal
{
public:
  ScenePortal() = default;

  void SetScene(const std::string& name);
  void Activate() const;

  void Render(TimeStep elapsed) override;

private:
  std::string m_SceneName;
};

