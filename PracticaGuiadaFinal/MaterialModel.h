#pragma once
#include "util.h"
#include "Solid.h"
#include "MaterialTriangle.h"
#include <GL/glut.h>

using namespace std;

class MaterialModel : public Solid
{
private:
	vector<MaterialTriangle> triangles;
public:
	MaterialModel() {}

	void AddMaterialTriangle(MaterialTriangle triangle);
	void Clear();
	void Render();
	MaterialModel* Clone();
};

