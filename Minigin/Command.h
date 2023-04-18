#pragma once
#include "PengoComponent.h"

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;
		virtual void Execute() = 0;

		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;
	};


	class MoveCommand : public Command
	{
	public:
		MoveCommand(std::shared_ptr<GameObject> obj, PengoComponent::PengoState movingDirection);
		void Execute() override;

	private:
		std::shared_ptr<GameObject> m_pObject;
		PengoComponent::PengoState m_PlayerState;
	};

	class DieCommand : public Command
	{
	public:
		DieCommand(std::shared_ptr<GameObject> obj);
		void Execute() override;

	private:
		std::shared_ptr<GameObject> m_pObject;
	};

	class GivePointsCommand : public Command
	{
	public:
		GivePointsCommand(std::shared_ptr<GameObject> obj, int );
		void Execute() override;

	private:
		std::shared_ptr<GameObject> m_pObject;
	};
}
