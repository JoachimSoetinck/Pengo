#include "MiniginPCH.h"
#include "GameObject.h"

#include <algorithm>


void dae::GameObject::Update()
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Update();
	}
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Update();
	}

}
void dae::GameObject::FixedUpdate()
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->FixedUpdate();
	}
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->FixedUpdate();
	}

}

void dae::GameObject::Render() const
{
	for (size_t i = 0; i < m_pComponents.size(); i++)
	{
		m_pComponents[i]->Render();
	}
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->Render();
	}

}

void dae::GameObject::Delete()
{
	m_MarkedForDelete = true;
}

void dae::GameObject::SetPosition(float x, float y)
{
	for (const auto& pChild : m_pChildren)
	{
		const auto pos{ pChild->GetLocalPosition() - m_Transform.GetLocalPosition() };
		pChild->SetPosition(pos.x + x, pos.y + y);
	}
	m_Transform.SetLocalPosition(x, y, 0.0f);
}



bool dae::GameObject::GetMarkedForDelete() const
{
	return m_MarkedForDelete;
}

void dae::GameObject::SetParent(dae::GameObject* parent, bool keepWorldPosition)
{
	if (parent)
	{
		if (keepWorldPosition)
		{
			m_Transform.SetLocalPosition(m_Transform.GetLocalPosition() + parent->GetLocalPosition());
			m_Transform.SetDirty();
		}
		

		if (m_pParent != parent && m_pParent)
		{
			m_pParent->RemoveChild(this);
		}
	}
	m_pParent = parent;
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}



std::vector<std::shared_ptr<dae::GameObject>> dae::GameObject::GetChildren() const
{
	return m_pChildren;
}

void dae::GameObject::RemoveChild(dae::GameObject* go)
{
	go->SetParent(nullptr);
	for (size_t i = 0; i < m_pChildren.size(); ++i)
	{
		if (m_pChildren[i].get() == go)
		{
			m_pChildren.clear();
			return;
		}
	}
}

void dae::GameObject::AddChild(std::shared_ptr<dae::GameObject> go, bool keepTransform)
{
	m_pChildren.emplace_back(go);
	go->SetParent(this, keepTransform);
}


dae::GameObject::~GameObject()
{
	for (size_t i = 0; i < m_pComponents.size(); ++i)
	{
		delete m_pComponents[i];
		m_pComponents[i] = nullptr;
	}

	m_pComponents.clear();
	m_pChildren.clear();
}

