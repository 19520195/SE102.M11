#pragma once
#include "Engine/Core/Base.hh"
#include <d3dx9.h>

typedef IDirect3DTexture9 Texture;

class TextureBase
{
public:
	TextureBase() = default;
	~TextureBase();
	static Ref<TextureBase> GetInstance();

	Texture* Add(const std::string& name, LPCWSTR path, D3DCOLOR trans);
	Texture* Get(const std::string& name);

private:
	static Ref<TextureBase> s_Instance;
	HashTable<std::string, Texture*> m_Textures;
};
