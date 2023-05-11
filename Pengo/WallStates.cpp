#include "WallStates.h"
#include "BaseState.h"
#include "SpriteCompenent.h"
#include "GameObject.h"
#include "Sprite.h"
#include "CollisionComponent.h"
#include "Timer.h"
#include "WallComponent.h"


dae::BaseState* dae::WallState::Update(GameObject* object)
{
	return nullptr;
}

void dae::WallState::Enter(GameObject* object)
{
	SDL_Rect  src = { 0,0,30,30 };
	object->GetComponent<dae::SpriteComponent>()->SetSprite(Sprite("Blocks.png", 1, 1, src));
}

void dae::WallState::Exit(GameObject* object)
{

}

dae::BaseState* dae::BorderState::Update(GameObject* object)
{
	return nullptr;
}

void dae::BorderState::Enter(GameObject* object)
{
	SDL_Rect  src = { 0,0,16,24 };
	object->GetComponent<dae::SpriteComponent>()->SetSprite(Sprite("Wall.png", 1, 1, src));
}

void dae::BorderState::Exit(GameObject* object)
{
}

dae::BaseState* dae::BreakingState::Update(GameObject * object)
{
	elapsedSec += Time::GetInstance().GetDeltaTime();

	if (elapsedSec >= durationBreaking)
	{
		elapsedSec = 0;
		return new GroundState();
	}
		

	return nullptr;
}

void dae::BreakingState::Enter(GameObject* object)
{
	SDL_Rect  src = { 0,0,32,32 };
	object->GetComponent<dae::SpriteComponent>()->SetSprite(Sprite("Blocks.png", 4, 2, src));
	object->GetComponent<dae::SpriteComponent>()->SetTimer(0.15f);
}

void dae::BreakingState::Exit(GameObject* object)
{
	object->Delete();
}

dae::BaseState* dae::GroundState::Update(GameObject* object)
{
	return nullptr;
}

void dae::GroundState::Enter(GameObject* object)
{
	object->GetComponent<dae::SpriteComponent>()->SetVisibility(false); 
	object->GetComponent<CollisionComponent>()->Disable();
	object->GetComponent<WallComponent>()->SetWallType(dae::WallComponent::WallType::Ground);
}

void dae::GroundState::Exit(GameObject* object)
{
}
