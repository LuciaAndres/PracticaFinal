#pragma once
#include "Solid.h"
#include <GL/glut.h>

class Camera : public Solid
{
private:

public:
	Camera() {}
	
	Camera(Vector3D positionArgument) 
	{
		this->SetCoordinates(positionArgument);
	}
	Solid* Clone();

	void Render();
};

