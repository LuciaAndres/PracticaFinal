#pragma once
class Collider
{
public:
	Collider() {}
	virtual bool CheckCollision(Collider& other) = 0;
	virtual void DebugRenderer() = 0;
	virtual ~Collider() {}
};

