#include "BlasterMaster.hh"
#include "Engine/Core/Game.hh"
#include "Engine/Renderer/Texture.hh"
#include "Engine/Renderer/Sprite.hh"
#include "Engine/Renderer/Animation.hh"
#include "Scene/SceneManager.hh"

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
  SceneManager::GetInstance()->LoadConfig("Resources/BM.ini");
  Game::GetInstance()->SetScene(SceneManager::GetInstance()->GetCurrentScene());
  Game::GetInstance()->Run(); 
  return EXIT_SUCCESS;
}
