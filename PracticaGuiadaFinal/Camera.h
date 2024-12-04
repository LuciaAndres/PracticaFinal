#pragma once
#include "Solid.h"
class Camera : public Solid
{
private:

public:
	Camera() {}
	

	Camera* Clone();

	void Render();
};

