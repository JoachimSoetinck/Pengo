#include "WallComponent.h"
#include "GameObject.h"
#include "SpriteCompenent.h"


dae::WallComponent::WallComponent(dae::GameObject* go, WallType wallType): BaseComponent(go),
m_WallType{wallType}, m_SpriteComp{nullptr}
{
	
}

void dae::WallComponent::Initialize()
{
	SDL_Rect src = { 0,0,30,30 };

	if (m_pGameObject->GetComponent<SpriteComponent>())
	{
		m_SpriteComp = m_pGameObject->GetComponent<SpriteComponent>();
		
		switch (m_WallType)
		{
		case WallType::Border: 
		{
			src = { 0,0,16,24 };
			m_SpriteComp->SetSprite(Sprite("Wall.png", 1, 1, src));
			break;
		}
		case WallType::MoveableWall: 
		{
			src = { 0,0,30,30 };
			m_SpriteComp->SetSprite(Sprite("Blocks.png", 1, 1, src));
			
			break;
		}
			 
		case WallType::EnemySpawn: 
		{
			break;
		}
		case WallType::Ground:
		{
			m_SpriteComp->SetVisibility(false);
			break;
		}
		default:
			break;
		}
	}
}

void dae::WallComponent::Update()
{
}

void dae::WallComponent::Render() const
{
}

void dae::WallComponent::FixedUpdate()
{
}
