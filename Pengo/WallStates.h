#pragma once
#include "BaseState.h"

namespace dae
{
	class WallState : public BaseState
	{
	public:
		WallState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
	};

	class BorderState : public BaseState
	{
	public:
		BorderState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:

	};

	class BreakingState : public BaseState
	{
	public:
		BreakingState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		float elapsedSec{0};
		float durationBreaking{ .85f };
	};

	class GroundState : public BaseState
	{
	public:
		GroundState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
	};


}
