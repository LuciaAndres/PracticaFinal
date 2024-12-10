#include "Player.h"
#include <algorithm>
bool Player::CheckCollision(Solid* other)
{
	return CollisionHandler.CheckCollision(other);
}

void Player::ProcessKeyPressed(unsigned char key, int px, int py)
{
	switch (key)
	{
	case 'w':
	case 'W':
		this->getFPS()->Update(playerStep);
		this->Update(this->playerStep);
		break;
	case 's':
	case 'S':
		this->Update(-1 * this->playerStep);
		this->getFPS()->Update(-1* playerStep);
		break;
	}
}

void Player::ProcessMouseMovement(int x, int y)
{
	if (this->GetMouseX() >= 0 && this->GetMouseY() >= 0)
	{
		float deltaX = x - this->GetMouseX();
		float deltaY = y - this->GetMouseY();
		float tempSensValue= 0.3f;

		Vector3D orientation = this->GetOrientation() + Vector3D((y - this->GetMouseY()) * tempSensValue, (x - this->GetMouseX()) * tempSensValue, 0);
		this->SetOrientation(orientation);
		this->view->SetOrientation(orientation);
	}
	this->SetMouseX(x);
	this->SetMouseY(y);
}
/*
Solid* Player::Clone()
{
	return nullptr;
}

void Player::Render()
{
	CollisionHandler.Render();
}
*/