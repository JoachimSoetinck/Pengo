#pragma once
#include "ResourceManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

struct Sprite
{
	int Cols{ 1 };
	int Rows{ 1 };

	SDL_Rect SrcRect{ 0,0 };
	SDL_Point OffSet{ 0,0 };
	SDL_Point StartPos{};

	Sprite() = default;
	Sprite(const std::string& texturePath, int cols, int rows, const SDL_Rect& srcRect, const SDL_Point& offset = {})
		:m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(texturePath))
		, Cols(cols)
		, Rows(rows)
		, SrcRect(srcRect)
		, OffSet(offset)
		, StartPos({ srcRect.x, srcRect.y })
	{

	}

	Sprite(const std::string& texturePath, int cols = 1, int rows = 1, const SDL_Point& startPos = {}, const SDL_Point& offset = {})
		:m_pTexture(dae::ResourceManager::GetInstance().LoadTexture(texturePath))
		, Cols(cols)
		, Rows(rows)
		, OffSet(offset)
		, StartPos(startPos)
	{
		int width, height;
		SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &width, &height);
		SrcRect = { startPos.x,startPos.y, width / cols,height / rows };
	}


	bool operator==(const Sprite& other) const
	{
		return Cols == other.Cols &&
			Rows == other.Rows &&
			OffSet.x == other.OffSet.x &&
			OffSet.y == other.OffSet.y &&
			StartPos.x == other.StartPos.x &&
			StartPos.y == other.StartPos.y &&
			SrcRect.x == other.SrcRect.x &&
			SrcRect.y == other.SrcRect.y &&
			SrcRect.w == other.SrcRect.w &&
			SrcRect.h == other.SrcRect.h;
	}
	const dae::Texture2D* GetTexture() const { return m_pTexture; }

	SDL_Point GetTextureDimensions() const
	{
		int width, height;
		SDL_QueryTexture(m_pTexture->GetSDLTexture(), NULL, NULL, &width, &height);
		return{ width,height };
	}
private:
	const dae::Texture2D* m_pTexture{ nullptr };
};
