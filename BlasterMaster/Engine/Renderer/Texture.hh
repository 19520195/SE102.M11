#pragma once

#include <d3dx9.h>

#include <memory>
#include <unordered_map>

class TextureBase
{
public:
	TextureBase() = default;
	~TextureBase();

	LPDIRECT3DTEXTURE9 InsertTexture(int ID, LPCWSTR path, D3DCOLOR trans);
	LPDIRECT3DTEXTURE9 GetTexture(size_t ID);

	static TextureBase* Get();

private:
	std::unordered_map<size_t, LPDIRECT3DTEXTURE9> m_Textures;

private:
	static std::shared_ptr<TextureBase> s_Instance;
};
