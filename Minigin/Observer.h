#pragma once
#pragma once
#include "GameObject.h"

namespace dae
{
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() {}
		virtual void OnNotify(int event, GameObject* gameObject) = 0;
	private:
	};
}