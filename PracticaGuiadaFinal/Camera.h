#pragma once
#include "Solid.h"
#include <GL/glut.h>

class Camera : public Solid
{
private:

public:
	Camera() {}
	

	Camera* Clone();

	void Render();
};

