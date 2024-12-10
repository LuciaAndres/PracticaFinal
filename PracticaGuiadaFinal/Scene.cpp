#include <iostream>
#include "Scene.h"

void Scene::AddGameObject(Solid* object)
{
	gameObjects.push_back(object);
}

void Scene::Render()
{
	this->camera->Render();
	for (auto& object : gameObjects)
	{
		object->Render();
	}
}

void Scene::Update(const float& time)
{
	Vector3D gravity = Vector3D(0, 0, 0);
	for (auto& object : gameObjects)
	{
		object->Update(time, gravity);
		checkBoundary(object);
	}
}

void Scene::checkBoundary(Solid* object)
{
	Vector3D oSpeed = object->GetSpeed();

	float SpeedX = oSpeed.GetX();
	float SpeedY = oSpeed.GetY();
	float SpeedZ = oSpeed.GetZ();

	if(object->GetCoordinates().GetX() > boundary.GetX() || object->GetCoordinates().GetX() < -1 * boundary.GetX())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX * -1, SpeedY, SpeedZ);
		object->SetSpeed(nSpeed);
	}
	if (object->GetCoordinates().GetY() > boundary.GetY() || object->GetCoordinates().GetY() < -1 * boundary.GetY())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX , SpeedY * -1, SpeedZ);
		object->SetSpeed(nSpeed);
	}
	if (object->GetCoordinates().GetZ() > boundary.GetZ() || object->GetCoordinates().GetZ() < -1 * boundary.GetZ())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX, SpeedY, SpeedZ * -1);
		object->SetSpeed(nSpeed);
	}
}

