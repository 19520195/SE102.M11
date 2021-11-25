#include "Engine/Core/Game.hh"
#include "Engine/Renderer/Texture.hh"
#include "Engine/Renderer/Sprite.hh"
#include "Engine/Renderer/Animation.hh"

void LoadResources()
{
  Animation* animation;
  TextureBase::Get()->InsertTexture(1, L"Resources\\Jason_and_Sophia_III.png", D3DCOLOR_XRGB(0, 57, 115));
  TextureBase::Get()->InsertTexture(2, L"Resources\\Full_Area_3_Open_Wolrd.png", D3DCOLOR_XRGB(0, 0, 0));
  LPDIRECT3DTEXTURE9 xArea3 = TextureBase::Get()->GetTexture(2);
  SpriteBase::GetInstance()->InsertSprite(20001, 0, 0, 832, 1600, xArea3);


  LPDIRECT3DTEXTURE9 xJasonAndSophiaIII = TextureBase::Get()->GetTexture(1);
  // SophiaIII Right gun
  animation = new Animation(100);
  animation->Add(20001);

  // SophiaIII Wheels
  SpriteBase::GetInstance()->InsertSprite(10001, 21, 30, 29, 38, xJasonAndSophiaIII);
  SpriteBase::GetInstance()->InsertSprite(10002, 21, 21, 29, 29, xJasonAndSophiaIII);
  SpriteBase::GetInstance()->InsertSprite(10003, 21, 12, 29, 20, xJasonAndSophiaIII);
  SpriteBase::GetInstance()->InsertSprite(10004, 21, 3, 29, 11, xJasonAndSophiaIII);

  // SophiaIII Body
  SpriteBase::GetInstance()->InsertSprite(10011, 12, 3, 20, 11, xJasonAndSophiaIII);
  SpriteBase::GetInstance()->InsertSprite(10012, 12, 12, 20, 20, xJasonAndSophiaIII);
  SpriteBase::GetInstance()->InsertSprite(10013, 12, 21, 20, 29, xJasonAndSophiaIII);
  SpriteBase::GetInstance()->InsertSprite(10014, 12, 30, 20, 38, xJasonAndSophiaIII);

  // SophiaIII Gun
  SpriteBase::GetInstance()->InsertSprite(10021, 3, 39, 11, 55, xJasonAndSophiaIII);
  SpriteBase::GetInstance()->InsertSprite(10031, 3, 12, 11, 20, xJasonAndSophiaIII);

  // SophiaIII Left Wheel
  animation = new Animation(100);
  animation->Add(10001);
  animation->Add(10002);
  animation->Add(10003);
  animation->Add(10004);
  AnimationBase::Get()->Add(101, animation);

  // SophiaIII Right Wheel
  animation = new Animation(100);
  animation->Add(10002);
  animation->Add(10003);
  animation->Add(10004);
  animation->Add(10001);
  AnimationBase::Get()->Add(102, animation);

  // SophiaIII Body
  animation = new Animation(100);
  animation->Add(10011);
  AnimationBase::Get()->Add(103, animation);

  // SophiaIII Right gun
  animation = new Animation(100);
  animation->Add(10021);
  AnimationBase::Get()->Add(104, animation);
  // SophiaIII Right gun
  animation = new Animation(100);
  animation->Add(10031);
  AnimationBase::Get()->Add(105, animation);
}

INT APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow)
{
  int tilesOfWidth = 16;
  int tilesOfHeight = 14;

  int screenWidth = tilesOfWidth * 16 * OX_SCREEN_ZOOM;
  int screenHeight = tilesOfHeight * 16 * OX_SCREEN_ZOOM;

  Game::GetInstance()->Create(screenWidth, screenHeight, L"Blaster Master", hInstance, nCmdShow);
  
  LoadResources();
  R_SophiaIII.SetPos(16 * 4, 16 * 8 - 4);
  R_SophiaIII.SetState(SOPHIAIII_IDLE_LEFT);
  R_SophiaIII.SetAnimation(105, 104, 103, 102);

  Game::GetInstance()->Run(); 
  return EXIT_SUCCESS;
}
