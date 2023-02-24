#include "MiniginPCH.h"
#include "Transform.h"

#include "GameObject.h"

void dae::Transform::UpdateWorldPosition()
{
	if (m_positionIsDirty)
	{
		m_positionIsDirty = false;
		if (m_pOwner)
			m_worldPosition = m_pOwner->GetWorldPosition() + m_localPosition;
		else
			m_worldPosition = m_localPosition;

	}
}

const glm::vec3& dae::Transform::GetLocalPosition() const
{
	return m_localPosition;
}

const glm::vec3& dae::Transform::GetWorldPosition()
{
	if (m_positionIsDirty)
		UpdateWorldPosition();

	return m_worldPosition;
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;

	m_positionIsDirty = true;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;
	m_positionIsDirty = true;
}

void dae::Transform::SetDirty()
{
	m_positionIsDirty = true;
}

dae::Transform::Transform(dae::GameObject* pGO)
	:m_pOwner(pGO)
{

}

dae::Transform::~Transform()
{
}
