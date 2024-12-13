#include <iostream>
#include "Scene.h"

void Scene::AddGameObject(Solid* object)
{
	gameObjects.push_back(object);
}

void Scene::AddCollider(std::unique_ptr<Collider> collider)
{
	colliders.push_back((std::move(collider)));
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
}

void Scene::Update(const float& time)
{
	for (size_t i = 0; i < colliders.size(); ++i) {
		for (size_t j = i + 1; j < colliders.size(); ++j) {
			if (colliders[i]->CheckCollision(*colliders[j])) {
				std::cout << "Collision detected between collider " << i << " and " << j << std::endl;
			}
		}
	}

	for (auto& collider : colliders) {
		collider->DebugRenderer();
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

