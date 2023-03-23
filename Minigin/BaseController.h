#pragma once
class BaseController
{
public:
	BaseController() = default;
	virtual ~BaseController() = default;

	virtual void Update() const = 0;
};


