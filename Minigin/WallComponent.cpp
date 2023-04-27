#include "WallComponent.h"
#include "GameObject.h"
#include "SpriteCompenent.h"
#include "WallManagers.h"


dae::WallComponent::WallComponent(dae::GameObject* go,int nr, WallType wallType): BaseComponent(go),
m_WallType{wallType}, m_SpriteComp{nullptr}, m_Nr{nr}
{
	
}

void dae::WallComponent::Initialize()
{
	SDL_Rect src = { 0,0,30,30 };
	dae::WallManager::GetInstance().AddComponent(this);

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

		m_Center = m_pGameObject->GetLocalPosition();
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

bool dae::WallComponent::IsPointInWall(glm::ivec2 p)
{
	
	SDL_Rect rect = { m_pGameObject->GetLocalPosition().x,m_pGameObject->GetLocalPosition().y, 
		m_SpriteComp->GetDestRect().w,m_SpriteComp->GetDestRect().x };

	if (p.x > rect.x && p.x < rect.x + rect.w && p.y > rect.y && p.y < rect.y + rect.h)
		return true;

	return false;

}
