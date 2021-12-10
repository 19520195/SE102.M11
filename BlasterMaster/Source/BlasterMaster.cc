#include "BlasterMaster.hh"
#include "Engine/Core/Game.hh"
#include "Engine/Renderer/Texture.hh"
#include "Engine/Renderer/Sprite.hh"
#include "Engine/Renderer/Animation.hh"
#include "Scene/SceneParser.hh"

PlayScene* GetSceneFromFile(const std::string& filename);

INT APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow)
{
  Game::GetInstance()->Create(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SCREEN_TITLE,
    hInstance, nCmdShow);
  std::shared_ptr<PlayScene> scene(GetSceneFromFile("Resources/Area3.ini"));
  Game::GetInstance()->SetScene(scene.get());
  Game::GetInstance()->Run(); 
  return EXIT_SUCCESS;
}

PlayScene* GetSceneFromFile(const std::string& filename)
{
  SceneParser parser(filename);
  if (!parser.Parse()) return nullptr;

  parser.PrintDebugInfo();
  PlayScene* scene = new PlayScene();
  for (auto object : parser.GetObjects())
    scene->AddObject(object);
  // scene->SetPlayer((Player*)parser.GetPlayer());
  // scene->SetKeyboardHandler(parser.GetKeyboardEvent());
  scene->SetBackground(SPRID_BACKGROUND);

  JasonS* jason = new JasonS();
  scene->SetPlayer(jason);
  scene->SetKeyboardHandler(jason->GetKeyboard());

  return scene;
}