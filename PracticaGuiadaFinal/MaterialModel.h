#pragma once
#include "util.h"
#include "Model.h"
#include "MaterialTriangle.h"
#include <GL/glut.h>
#include "OBB.h"

using namespace std;

class MaterialModel : public Model
{
private:
	vector<MaterialTriangle> triangles;
	MeshCollider obb;
public:
	MaterialModel() {}

	void AddMaterialTriangle(MaterialTriangle triangle);
	const std::vector<MaterialTriangle>& GetTriangles() const {
		return triangles;
	}
	void Clear();
	void Render();

	MeshCollider& GetOBB() { return obb; }
	void SetOBB(const MeshCollider& newObb) { obb = newObb; }

	MaterialModel* Clone();
};

