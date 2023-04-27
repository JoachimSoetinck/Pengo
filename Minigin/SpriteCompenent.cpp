#include "MiniginPCH.h"
#include "SpriteCompenent.h"

#include "GameObject.h"
#include "Timer.h"


dae::SpriteComponent::SpriteComponent(dae::GameObject* pGO, const Sprite& sourcePart, const SDL_Rect& dstRect, float animationTime, bool flip)
	:BaseComponent(pGO)
	, m_Sprite(sourcePart)
	, m_AnimationTime(animationTime)
	, m_DstRect(dstRect)
	, m_Flip(flip)
{
	if (dstRect.w == dstRect.h && dstRect.w == 0)
	{
		const auto dim = m_Sprite.GetTextureDimensions();
		m_DstRect.w = dim.x / m_Sprite.Cols;
		m_DstRect.h = dim.y / m_Sprite.Rows;
	}
}

void dae::SpriteComponent::Initialize()
{
}

void dae::SpriteComponent::Update()
{
	m_curTimer += dae::Time::GetInstance().GetDeltaTime();
	if (m_curTimer >= m_AnimationTime)
	{
		UpdateFrame();
		m_curTimer -= m_AnimationTime;
	}
}

void dae::SpriteComponent::FixedUpdate()
{
}

void dae::SpriteComponent::Render() const
{
	const auto pos = GetGameObject()->GetLocalPosition();

	if (m_isVisible)
	{
		const SDL_Rect dstRect{ static_cast<int>(m_DstRect.x + pos.x), static_cast<int>(m_DstRect.y + pos.y), m_DstRect.w,m_DstRect.h };

		const auto texture = m_Sprite.GetTexture();

		dae::Renderer::GetInstance().RenderTexture(*texture, m_Sprite.SrcRect, dstRect, m_Rotation, m_Flip);
	}
	
}

void dae::SpriteComponent::SetFlip(bool flip)
{
	m_Flip = flip;
}

void dae::SpriteComponent::SetRotation(float angle)
{
	m_Rotation = angle;
}

void dae::SpriteComponent::ResetSprite()
{

	m_Flip = false;
	m_HasEnded = false;
	m_curTimer = 0;
	m_currentCol = 1;
	m_currentRow = 1;

}

void dae::SpriteComponent::UpdateFrame()
{
	if (m_currentCol != m_Sprite.Cols)
	{
		++m_currentCol;
	}
	else
	{
		m_currentCol = 1;
		if (m_currentRow != m_Sprite.Rows)
		{
			++m_currentRow;
		}
		else
		{
			m_currentRow = 1;
			m_HasEnded = true;
		}
		m_Sprite.SrcRect.y = static_cast<int>((m_currentRow - 1) * (m_Sprite.SrcRect.h + m_Sprite.OffSet.y) + m_Sprite.StartPos.y);
	}
	m_Sprite.SrcRect.x = static_cast<int>((m_currentCol - 1) * (m_Sprite.SrcRect.w + m_Sprite.OffSet.x) + m_Sprite.StartPos.x);
}

