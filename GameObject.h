#pragma once
#include "Vector2D.h"


class GameObject
{
protected:
	bool GetKey(WPARAM keyName);
	float getDeltaTime();
	Vector2D<int> getMousePos();
public:	
	virtual void Start() {};
	virtual void Update() {};
	virtual ~GameObject() {};
};