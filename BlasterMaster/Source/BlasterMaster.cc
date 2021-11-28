#include "BlasterMaster.hh"
#include "Engine/Core/Game.hh"
#include "Engine/Renderer/Texture.hh"
#include "Engine/Renderer/Sprite.hh"
#include "Engine/Renderer/Animation.hh"

void LoadResources();

INT APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow)
{
  Game::GetInstance()->Create(SCREEN_WIDTH, SCREEN_HEIGHT, L"Blaster Master", hInstance, nCmdShow);
  
  LoadResources();
  R_SophiaIII.SetPos(100, 100);
  R_SophiaIII.SetState(SOPHIAIII_IDLE_LEFT);

  Game::GetInstance()->Run(); 
  return EXIT_SUCCESS;
}

void LoadResources()

{
  Animation* animation;
  TextureBase::Get()->InsertTexture(1, L"Resources\\SophiaIII.png", D3DCOLOR_XRGB(0, 57, 115));
  TextureBase::Get()->InsertTexture(2, L"Resources\\Full_Area_3_Open_Wolrd.png", D3DCOLOR_XRGB(0, 0, 0));
  LPDIRECT3DTEXTURE9 xArea3 = TextureBase::Get()->GetTexture(2);
  SpriteBase::GetInstance()->Add(20001, 0, 0, 832, 1600, xArea3);

  LPDIRECT3DTEXTURE9 TXSophiaIII = TextureBase::Get()->GetTexture(1);

  // Barrel
  SpriteBase::GetInstance()->Add(10101,  1,  1,  9,  9, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10102,  1, 10,  9, 18, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10103,  1, 19,  9, 27, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10104,  1, 28,  9, 36, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10105,  1, 37,  9, 45, TXSophiaIII);

  // Grip
  SpriteBase::GetInstance()->Add(10201, 10,  1, 18,  9, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10201, 10, 10, 18, 18, TXSophiaIII);

  // Wheel
  SpriteBase::GetInstance()->Add(10301, 19,  1, 27,  9, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10302, 19, 10, 27, 18, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10303, 19, 19, 27, 27, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10304, 19, 28, 27, 36, TXSophiaIII);

  // Hammer
  SpriteBase::GetInstance()->Add(10401, 28,  1, 36, 17, TXSophiaIII);
  SpriteBase::GetInstance()->Add(10402, 28, 19, 36, 35, TXSophiaIII);
  
  // LWheel
  animation = new Animation(100);
  animation->Add(10301);
  animation->Add(10302);
  animation->Add(10303);
  animation->Add(10304);
  AnimationBase::GetInstance()->Add(10301, animation);

  // RWheel
  animation = new Animation(100);
  animation->Add(10302);
  animation->Add(10303);
  animation->Add(10304);
  animation->Add(10301);
  AnimationBase::GetInstance()->Add(10302, animation);
}