#pragma once

#include <d3dx9.h>

#include <memory>
#include <unordered_map>

typedef IDirect3DTexture9 Texture;

class TextureBase
{
public:
	TextureBase() = default;
	~TextureBase();

	Texture* Add(int ID, LPCWSTR path, D3DCOLOR trans);
	Texture* Get(size_t ID);

	static TextureBase* GetInstance();

private:
	std::unordered_map<size_t, Texture*> m_Textures;

private:
	static std::shared_ptr<TextureBase> s_Instance;
};
