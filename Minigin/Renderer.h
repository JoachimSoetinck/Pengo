#pragma once
#include <SDL.h>
#include "Singleton.h"


namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, const double angle) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const  double angle, const SDL_Point* center) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, float x, float y, const double angle) const;




		void RenderTexture(const Texture2D& texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect, const double& angle, bool flipped) const;


		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	
	};
}

