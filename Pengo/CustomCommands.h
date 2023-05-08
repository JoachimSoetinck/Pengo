#pragma once
#include "PengoComponent.h"
#include "Command.h"


namespace dae {
	class MoveCommand : public Command
	{
	public:
		MoveCommand(std::shared_ptr<GameObject> obj, PengoComponent::PengoState movingDirection);
		void Execute() override;

	private:
		std::shared_ptr<GameObject> m_pObject;
		PengoComponent::PengoState m_PlayerState;
	};

	class PushCommand : public Command
	{
	public:
		PushCommand(std::shared_ptr<GameObject> obj);
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
		GivePointsCommand(std::shared_ptr<GameObject> obj, int);
		void Execute() override;

	private:
		std::shared_ptr<GameObject> m_pObject;
	};
}
class CustomCommands
{
};

