#pragma once
#include "Solid.h"
#include <string>
#include <GL/glut.h>

class Text : public Solid
{
private:
	
	std::string text;

public:
	Text() :
		Solid(), text(0) {}
	
	void Render();
	Text* Clone();
};

