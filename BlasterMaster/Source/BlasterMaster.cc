#include "BlasterMaster.hh"
#include "Engine/Core/Game.hh"
#include "Engine/Renderer/Texture.hh"
#include "Engine/Renderer/Sprite.hh"
#include "Engine/Renderer/Animation.hh"
#include "Scene/SceneParser.hh"

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
  
  SophiaIII __SophiaIII;
  __SophiaIII.SetXY(1160, 480);
  int state = __SophiaIII.GetState();
  // __SophiaIII.SetState(SD_SET_RIGHT(state));

  std::shared_ptr<PlayScene> scene(new PlayScene);
  {
    SceneParser parser("Resources/Area3.ini");
    parser.Parse();
    parser.PrintDebugInfo();

    for (auto object : parser.GetObjects())
      scene->AddObject(object);
    scene->SetBackground(SPRID_BACKGROUND);
  }
  scene->SetPlayer(&__SophiaIII);

  std::unique_ptr<SophiaIIIKeyboardEvent> keyboard(new SophiaIIIKeyboardEvent());
  keyboard->m_SophiaIII = &__SophiaIII;
  scene->SetKeyboardHandler(keyboard.get());

  Game::GetInstance()->SetScene(scene.get());
  Game::GetInstance()->Run(); 
  return EXIT_SUCCESS;
}
