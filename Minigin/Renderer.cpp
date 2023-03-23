#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl2.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}




}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();


	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const double angle) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}



void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, double angle, const SDL_Point* center) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, center, SDL_RendererFlip::SDL_FLIP_NONE);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, float x, float y, const double angle) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(srcRect.w);
	dst.h = static_cast<int>(srcRect.h);

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dst, angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
}


void dae::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const double& angle, bool flipped) const
{
	if (flipped)
	{
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angle, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else
		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &srcRect, &dstRect, angle, nullptr, SDL_FLIP_NONE);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }