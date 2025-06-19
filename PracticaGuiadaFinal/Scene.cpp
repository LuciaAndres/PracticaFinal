#include <iostream>
#include "Scene.h"

void Scene::AddGameObject(Solid* object)
{
	gameObjects.push_back(object);
}


void Scene::AddHiddenObject(Solid* object)
{
	object->SetIsHidden(true);
	AddGameObject(object);
}

void Scene::Render()
{
	this->camera->Render();

	for (auto& object : gameObjects)
	{
		if (!object->GetIsHidden())
		{
			object->Render();
		}
	}

	if (scenarioCollider) {
		//scenarioCollider->RenderBoundingBoxes(); // Draw bounding boxes
	}

}

void Scene::Update(const float& time) {
	for (auto& object : gameObjects) {
		object->Update(time, Vector3D(0, -9.81f, 0));
	}
}

MeshCollider* Scene::GetScenarioCollider() {
	return scenarioCollider.get();
}

void Scene::SetScenarioCollider(std::unique_ptr<MeshCollider> collider) {
	scenarioCollider = std::move(collider);
}

void Scene::checkBoundary(Solid* object)
{
	Vector3D oSpeed = object->GetSpeed();

	float SpeedX = oSpeed.GetX();
	float SpeedY = oSpeed.GetY();
	float SpeedZ = oSpeed.GetZ();

	if (object->GetCoordinates().GetX() > boundary.GetX() || object->GetCoordinates().GetX() < -1 * boundary.GetX())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX * -1, SpeedY, SpeedZ);
		object->SetSpeed(nSpeed);
	}
	if (object->GetCoordinates().GetY() > boundary.GetY() || object->GetCoordinates().GetY() < -1 * boundary.GetY())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX, SpeedY * -1, SpeedZ);
		object->SetSpeed(nSpeed);
	}
	if (object->GetCoordinates().GetZ() > boundary.GetZ() || object->GetCoordinates().GetZ() < -1 * boundary.GetZ())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX, SpeedY, SpeedZ * -1);
		object->SetSpeed(nSpeed);
	}
}

void Scene::AddRamp(Vector3D start, Vector3D end, Vector3D control)
{
}

bool Scene::CheckRampCollision(const OBB& other)
{
	return false;
}