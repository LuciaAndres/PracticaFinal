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
		Solid(), text("null") {}
	
	void Render();
	Text* Clone();
};

