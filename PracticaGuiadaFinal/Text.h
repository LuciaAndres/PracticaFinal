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

	Text(string text) :
		Solid(), text(text) {}

	Text* Clone();
	void Render();
	void renderOnScreenAt(float x, float y);

	inline string getText() const { return this->text; }
	inline void setText(const string& textToSet) { this->text = textToSet; }
};

