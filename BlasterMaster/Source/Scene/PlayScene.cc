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
  m_Camera.SetWidth(SCREEN_WIDTH);
  m_Camera.SetHeight(SCREEN_HEIGHT);

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
    m_ScreenWidth = obParser.GetScreenWidth();
    m_ScreenHeight = obParser.GetScreenHeight();
    float square = std::max(m_ScreenWidth, m_ScreenHeight);
    m_QuadTree = CreateScope<QuadTree>(square, square);
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
  // Cache for multiple retrieve
  TimeStep currentFrameTime = Game::GetInstance()->GetLastFrameTime();
  if (m_LastGetObject == currentFrameTime)
    return m_Objects;
  m_LastGetObject = currentFrameTime;
  
  Box2F active;
  active.SetLocation(m_Camera.GetLocation() - m_Camera.GetSize() / 2.f);
  active.SetSize(m_Camera.GetSize() * 2.f);
  m_Objects = m_QuadTree->Retrieve(active);
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

Ref<Object> PlayScene::FindRef(Object* object) const
{
  for (const auto& ref : m_Objects)
    if (ref.get() == object)
      return ref;
  return nullptr;
}

void PlayScene::AddObject(Ref<Object> object)
{
  m_QuadTree->Insert(object);
}

void PlayScene::AddBounding(Ref<BoundingBox> box)
{
  m_Boxes.emplace_back(box);
}

void PlayScene::Update(TimeStep elapsed)
{
  m_Objects = this->GetObjects();
  m_Camera.SetCenter(m_Player->GetLocation());

  if (m_Camera.GetX() < 0) m_Camera.SetX(0);
  if (m_Camera.GetY() < 0) m_Camera.SetY(0);
  
  if (m_ScreenWidth != 0)
  {
    if (m_Camera.GetRight() > m_ScreenWidth) m_Camera.SetX(m_ScreenWidth - SCREEN_WIDTH);
    if (m_Camera.GetTop() > m_ScreenHeight) m_Camera.SetX(m_ScreenHeight - SCREEN_HEIGHT);
  }


  // Colliders
  List<Ref<Collider2D>> colliders;
  for (const auto& object : m_Objects)
    if (Ref<Collider2D> collider = object->GetCollider())
      colliders.emplace_back(collider);

  Physics::Calculate(colliders);
  for (auto& collider : colliders)
    collider->UpdateRefer();

  for (auto& object : m_Objects)
    if (object->IsDied())
      m_QuadTree->Remove(object);
}

void PlayScene::Render(TimeStep elapsed)
{
  // 3 layers 
  // L2 - Foreground
  // L1 - Objects
  // L0 - Bounding boxes
  // L0 - Background

  m_Background->Render(0, 0);
  for (const auto& box : m_Boxes) box->Render();
  m_Boxes.clear();

  for (const auto& object : this->GetObjects())
    object->Render(elapsed);
  m_Player->Render(elapsed);
  m_Foreground->Render(0, 0);
}
