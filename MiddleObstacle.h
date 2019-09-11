#pragma once

#include "GameObject.h"
#include "Collider.h"

class MiddleObstacle
	: virtual public GameObject, virtual public Colider
{
	//std::vector<Vector2D<int>> vertexInfo;
	//int Tag;
private:
	int* followingx;
	float cntAfterColide;
public:
	void Update() override;
	MiddleObstacle(int* following, int left, int top, int right, int bottom);
	void OnCollision(int destTag) override;
};