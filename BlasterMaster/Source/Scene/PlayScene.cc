#include "PlayScene.hh"
#include "SceneParser.hh"
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

  SceneParser obParser(oFile);
  if (!obParser.Parse()) DEBUG_MSG(L"Can not parse file %s\n", TO_LPWSTR(oFile));
  else
  {
    m_QuadTree = CreateScope<QuadTree>(1600.f, 784.f);
    for (auto object : obParser.GetObjects())
      m_QuadTree->Insert(object);

    this->SetPlayer(obParser.GetPlayer());
    this->SetKeyboardHandler(obParser.GetKeyboardEvent());
  }
}

Player* PlayScene::GetPlayer() const
{
  return m_Player.get();
}

std::vector<Object*> PlayScene::GetObjects() const
{
  Box2F viewport(m_Camera, SCREEN_WIDTH, SCREEN_HEIGHT);
  return m_QuadTree->Retrieve(viewport);
}

void PlayScene::SetPlayer(Ref<Player> player)
{
  m_Player = player;
  SetKeyboardHandler(player->GetKeyboard());
}

void PlayScene::SetKeyboardHandler(Ref<KeyboardEvent> handler)
{
  m_Keyboard = handler;
  Input::GetInstance()->SetKeyHandler(m_Keyboard);
}

void PlayScene::AddObject(Object* object)
{
  m_QuadTree->Insert(object);
}

void PlayScene::Update(TimeStep elapsed)
{
  m_Objects = this->GetObjects();
  m_Player->Update(elapsed, m_Objects);

  m_Camera.SetXY(m_Player->GetX() - 100, m_Player->GetY() - 100);
  if (m_Camera.GetX() < 0) m_Camera.SetX(0);
  if (m_Camera.GetY() < 0) m_Camera.SetY(0);
  if (m_Camera.GetX() > 1344) m_Camera.SetX(1344);
  if (m_Camera.GetY() > 560) m_Camera.SetY(560);

  // SophiaIII* s3 = dynamic_cast<SophiaIII*>(m_Player);
  // for (const auto& bullet : s3->GetBullets())
  //   bullet->Update(elapsed, m_Objects);

  for (auto& object : m_Objects)
    if (object->IsDied() == false)
      object->Update(elapsed);
}

void PlayScene::Render(TimeStep elapsed)
{
  #ifdef _DEBUG
  Texture* DEBUG_RED_BBOX  = nullptr; // TextureBase::GetInstance()->Get(TEXID_RED_BBOX);
  Texture* DEBUG_BLUE_BBOX = nullptr; // TextureBase::GetInstance()->Get(TEXID_BLUE_BBOX);
  #endif // _DEBUG

  // Draw background
  SpriteBase::GetInstance()->Get("Background")->Render(0, 0);

  for (size_t i = 0; i < DEBUG_COLLISION.size(); ++i)
  {
    const auto& object = m_Objects[i];
    if (!object->IsDied())
    {
      object->Render(elapsed);

      #ifdef _DEBUG
      Texture* bbox = (DEBUG_COLLISION[i] ? DEBUG_RED_BBOX : DEBUG_BLUE_BBOX); 
      Sprite sprite(0, 0, object->GetHeight(), object->GetWidth(), bbox);
      Renderer::DrawSprite(object->GetX(), object->GetY(), &sprite);
      #endif // _DEBUG
    }
  }

  // for (const auto& bullet : (static_cast<SophiaIII*>(m_Player))->GetBullets())
  // {
  //   if (bullet->IsDied() == false)
  //   {
  //     const auto& object = bullet;
  //     object->Render(elapsed);
  // 
  //     #ifdef _DEBUG
  //     Sprite sprite(0, 0, 0, object->GetHeight(), object->GetWidth(), DEBUG_BLUE_BBOX);
  //     Renderer::DrawSprite(object->GetX(), object->GetY(), &sprite);
  //     #endif // _DEBUG
  //   }
  // }

  m_Player->Render(elapsed);
  #ifdef _DEBUG
  Sprite sprite(0, 0, m_Player->GetHeight(), m_Player->GetWidth(), DEBUG_BLUE_BBOX);
  Renderer::DrawSprite(m_Player->GetX(), m_Player->GetY(), &sprite);
  #endif // _DEBUG

  SpriteBase::GetInstance()->Get("Foreground")->Render(0, 0);
}
