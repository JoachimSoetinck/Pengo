#pragma once

#include "glm/common.hpp"
#include <glm/fwd.hpp>

namespace dae
{
	class GameObject;

	class Transform final
	{
	public:
		Transform() = default;
		Transform(GameObject* gameObject);
		~Transform();

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;


		//Getters
		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		double GetRotation() const;
		const glm::vec2& GetCenter();


		//Setters
		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& pos);

		void SetRotation(int angle);
		void SetDirty();
	private:
		//Update
		void UpdateWorldPosition();

		GameObject* m_pOwner;
		glm::vec3 m_localPosition;
		glm::vec3 m_worldPosition;

		double m_localRotation{ 0.0000000000000000 };


		glm::vec2 m_center;
		bool m_positionIsDirty = false;
	};
};

