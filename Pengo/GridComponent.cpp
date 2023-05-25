#include "GridComponent.h"
#include "GameObject.h"
#include "MiniginPCH.h"
#include "Sprite.h"
#include "SpriteCompenent.h"
#include "CollisionComponent.h"
#include "TextComponent.h"
#include "WallComponent.h"
#include "Renderer.h"
#include "RigidBody.h"
#include "GameInfo.h"
#include "WallManagers.h"


GridComponent::GridComponent(dae::GameObject* go, int columns, int rows, std::vector<int> walls, std::vector<int> enemySpawners, glm::ivec2 startpos, SDL_Rect dest) : BaseComponent(go),
m_Rows{ rows },
m_Colums{ columns },
m_StartPos{ startpos },
m_BlockSize{ dest },
m_Wallpositions{ walls },
m_EnemySpawners{ enemySpawners }
{
}

void GridComponent::Initialize()
{
	dae::GameInfo::GetInstance().SetGameObject(m_pGameObject);
	SDL_Rect src = { 0,0,30,30 };
	SDL_Rect collisionSize = { 0,0,24,24 };
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);


	int nr = 0;
	for (int i = 0; i < m_Colums; ++i)
	{
		for (int j = 0; j < m_Rows; ++j)
		{
			auto go = std::make_shared<dae::GameObject>();
			go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Blocks.png", 1, 1, src), m_BlockSize));
			go->AddComponent(new dae::RigidBody(go.get(), { 200,200 }));
			dae::WallComponent* wallcomponent;
			if (std::find(m_Wallpositions.begin(), m_Wallpositions.end(), nr) != m_Wallpositions.end())
			{
				wallcomponent = new dae::WallComponent(go.get(), nr);
			}

			else
				wallcomponent = new dae::WallComponent(go.get(), nr, dae::WallComponent::WallType::Ground);


			if (std::find(m_EnemySpawners.begin(), m_EnemySpawners.end(), nr) != m_EnemySpawners.end())
			{
				wallcomponent->MakeSpawner();
			}


			go->AddComponent(wallcomponent);
			go->AddComponent(new dae::CollisionComponent(go.get(), collisionSize));
			go->SetPosition(m_StartPos.x + i * m_BlockSize.w, 75 + j * m_BlockSize.w);

			m_pGameObject->AddChild(go);
			++nr;
		}
	}

	src = { 0,0,16,24 };

	int offset = 25;
	for (int i = -1; i <= m_Colums; ++i)
	{
		++nr;
		auto go = std::make_shared<dae::GameObject>();
		go = std::make_shared<dae::GameObject>();
		go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, src), m_BlockSize, 0.8f));
		go->AddComponent(new dae::WallComponent(go.get(), nr, dae::WallComponent::WallType::Border));
		go->AddComponent(new dae::CollisionComponent(go.get(), collisionSize));
		go->SetPosition(m_StartPos.x + i * m_BlockSize.w, 50);
		m_pGameObject->AddChild(go);

		go = std::make_shared<dae::GameObject>();
		go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, src), m_BlockSize, 0.8f));
		go->AddComponent(new dae::WallComponent(go.get(), nr, dae::WallComponent::WallType::Border));
		go->AddComponent(new dae::CollisionComponent(go.get(), collisionSize));
		go->SetPosition(m_StartPos.x + i * m_BlockSize.w, 50 + (m_Rows + 1) * m_BlockSize.w);
		m_pGameObject->AddChild(go);
	}

	for (int i = 0; i <= m_Colums + 1; ++i)
	{
		++nr;
		auto go = std::make_shared<dae::GameObject>();
		go = std::make_shared<dae::GameObject>();
		go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, src), { 0,0,25,25 }, 0.8f));
		go->AddComponent(new dae::WallComponent(go.get(), nr, dae::WallComponent::WallType::Border));
		go->AddComponent(new dae::CollisionComponent(go.get(), collisionSize));
		go->SetPosition((m_StartPos.x - offset), 75 + m_BlockSize.w * i);
		m_pGameObject->AddChild(go);

		go = std::make_shared<dae::GameObject>();
		go->AddComponent(new dae::SpriteComponent(go.get(), Sprite("Wall.png", 1, 1, src), { 0,0,25,25 }, 0.8f));
		go->AddComponent(new dae::WallComponent(go.get(), nr, dae::WallComponent::WallType::Border));
		go->AddComponent(new dae::CollisionComponent(go.get(), collisionSize));
		go->SetPosition((m_StartPos.x - offset) + (m_Colums + 1) * m_BlockSize.w, 75 + m_BlockSize.w * i);
		m_pGameObject->AddChild(go);
	}
}

void GridComponent::Update()
{
}

void GridComponent::Render() const
{
	for (auto child : m_pGameObject->GetChildren())
	{
		auto p = child.get()->GetLocalPosition();
		p.x += child.get()->GetComponent<dae::SpriteComponent>()->GetDestRect().w / 2;
		p.y += child.get()->GetComponent<dae::SpriteComponent>()->GetDestRect().h / 2;

		if (child->GetComponent<dae::WallComponent>())
		{
			SDL_SetRenderDrawColor(dae::Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 0);
			SDL_RenderDrawPoint(dae::Renderer::GetInstance().GetSDLRenderer(), p.x, p.y);
		}

	}
}

void GridComponent::FixedUpdate()
{
}
