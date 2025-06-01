#pragma once
#include "util.h"
#include "Model.h"
#include "MaterialTriangle.h"
#include <GL/glut.h>

using namespace std;

class MaterialModel : public Model
{
private:
	vector<MaterialTriangle> triangles;
public:
	MaterialModel() {}

	void AddMaterialTriangle(MaterialTriangle triangle);
	
	void Clear();
	void Render();
	Solid* Clone();
};

