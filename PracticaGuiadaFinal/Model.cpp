#include "Model.h"
void Model::Render()
{

	glPushMatrix();
	glTranslatef(this->GetCoordinates().GetX(), this->GetCoordinates().GetY(), this->GetCoordinates().GetZ());
	glColor3f(this->GetColor().GetRed(), this->GetColor().GetGreen(), this->GetColor().GetBlue());
	glRotatef(this->GetOrientation().GetX(), 1.0, 0.0, 0.0);
	glRotatef(this->GetOrientation().GetY(), 0.0, 1.0, 0.0);
	glRotatef(this->GetOrientation().GetZ(), 0.0, 0.0, 1.0);

	for (Triangle& t : triangles)
	{
		t.Render();
	}

	glPopMatrix();
}

void Model::AddTriangle(Triangle triangle)
{
	triangles.push_back(triangle);
}

void Model::Clear()
{
	triangles.clear();
}

void Model::PaintColor(Color color)
{
	for (Triangle& triangle : this->triangles)
	{
		triangle.setColor0(color);
		triangle.setColor1(color);
		triangle.setColor2(color);
	}
}

bool Model::CheckCollisionWithCapsule(CapsuleCollider& capsule)
{
	for (auto& triangle : triangles) {
		if (capsule.CheckCollisionWithTriangle(triangle)) {
			return true;
		}
	}
	return false;
}

Collider* Model::CreateMeshColliderFromModel(Model& model) {
	std::vector<Triangle> meshTriangles = model.GetTriangles();
	std::unique_ptr<MeshCollider> meshCollider = std::make_unique<MeshCollider>(meshTriangles);
	return meshCollider.release();
}

Solid* Model::Clone()
{
	return nullptr;
}