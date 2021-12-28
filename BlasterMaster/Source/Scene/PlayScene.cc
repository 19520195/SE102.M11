#include "PlayScene.hh"
#include "SceneParser.hh"
#include "Engine/Core/Game.hh"
#include "Engine/Core/Input.hh"

PlayScene::PlayScene()
{
  m_Player = nullptr; 
}

PlayScene::PlayScene(const std::string& rFile, const std::string& oFile)
{
  m_Player = nullptr;

  SceneParser rcParser(rFile);
  if (!rcParser.Parse())
    DEBUG_MSG(L"Can not parse file %s\n", TO_LPWSTR(rFile));
  else
  {
    m_Background = SpriteBase::GetInstance()->Get("Background");
    m_Foreground = SpriteBase::GetInstance()->Get("Foreground");
  }

  SceneParser obParser(oFile);
  if (!obParser.Parse()) DEBUG_MSG(L"Can not parse file %s\n", TO_LPWSTR(oFile));
  else
  {
    // m_QuadTree = CreateScope<QuadTree>(1600.f, 784.f);
    m_QuadTree = CreateScope<QuadTree>(512.f, 2016.f);
    m_QuadTree->Insert(obParser.GetObjects());

    this->SetPlayer(obParser.GetPlayer());
    this->SetKeyboardHandler(obParser.GetKeyboardEvent());
  }
}

Player* PlayScene::GetPlayer() const
{
  return m_Player.get();
}

std::vector<Ref<Object>> PlayScene::GetObjects()
{
  TimeStep currentFrameTime = Game::GetInstance()->GetLastFrameTime();
  if (m_LastGetObject == currentFrameTime)
    return m_Objects;
  m_LastGetObject = currentFrameTime;
  
  Box2F viewport(m_Camera, SCREEN_WIDTH, SCREEN_HEIGHT);
  m_Objects = m_QuadTree->Retrieve(viewport);
  return m_Objects;
}

void PlayScene::SetPlayer(Ref<Player> player)
{
  if (m_Player = player)
    SetKeyboardHandler(player->GetKeyboard());
}

void PlayScene::SetKeyboardHandler(Ref<KeyboardEvent> handler)
{
  m_Keyboard = handler;
  Input::GetInstance()->SetKeyHandler(m_Keyboard);
}

void PlayScene::AddObject(Ref<Object> object)
{
  m_QuadTree->Insert(object);
}

void PlayScene::Update(TimeStep elapsed)
{
  m_Objects = this->GetObjects();
  m_Camera.SetXY(m_Player->GetX() - 100, m_Player->GetY() - 100);
  if (m_Camera.GetX() < 0) m_Camera.SetX(0);
  if (m_Camera.GetY() < 0) m_Camera.SetY(0);
  // if (m_Camera.GetX() > 1344) m_Camera.SetX(1344);
  // if (m_Camera.GetY() > 560) m_Camera.SetY(560);

  for (auto& object : m_Objects)
    if (object->IsDied() == false)
      object->Update(elapsed, m_Objects);
    else m_QuadTree->Remove(object);  
}

void PlayScene::Render(TimeStep elapsed)
{
  // 3 layers 
  // L2 - Foreground
  // L1 - Objects
  // L0 - Background

  m_Background->Render(0, 0);
  
  // auto _hi = TextureBase::GetInstance()->Get("Blue-BBox");
  // for (const auto& object : this->GetObjects())
  //   Sprite(0, 0, object->GetHeight(), object->GetWidth(), _hi)
  //     .Render(object->GetX(), object->GetY());

  for (const auto& object : this->GetObjects())
    object->Render(elapsed);
  m_Foreground->Render(0, 0);
}
