#include "Player.h"
#include <algorithm>
#include <cstdlib>

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
		this->view->Update(playerStep);
		this->Update(this->playerStep, gravity);
		break;
	case 's':
	case 'S':
		this->Update(-1 * this->playerStep, gravity);
		this->view->Update(-1* playerStep);
		break;
	case 'a':
	case 'A':
		this->Strafe(-1);
		break;
	case 'd':
	case 'D':
		this->Strafe(1);
		break;
	case 'e':
	case 'E':
		exit(0);
		break;
	default:
		std::cout << "Key Pressed: " << key << " is not valid" << std::endl;
		break;
	}
}

void Player::ProcessMouseMovement(int x, int y)
{
	
	static bool firstMouse = true;

	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	int centerX = windowWidth / 2;
	int centerY = windowHeight / 2;

	if(!firstMouse)
	{

		float deltaX = x - centerX;
		float deltaY = y - centerY;

		float tempSensValue = 0.3f;


		Vector3D orientation = this->GetOrientation() + Vector3D(deltaY * tempSensValue, deltaX * tempSensValue, 0);

		orientation.SetX(Clamp(orientation.GetX(), -89.0f, 89.0f));

		this->SetOrientation(orientation);
		this->view->SetOrientation(orientation);

	}

	firstMouse = false;

	glutWarpPointer(centerX, centerY);
}

void Player::Strafe(float direction)
{
	float yOrientation = degToRad(this->GetOrientation().GetY());

	float xComponent = cos(yOrientation) * direction; 
	float zComponent = sin(yOrientation) * direction;

	Vector3D strafeVector(xComponent, 0, zComponent);

	Vector3D newCoordinates = this->GetCoordinates() + strafeVector * playerStep;
	this->SetCoordinates(newCoordinates);
	this->view->SetCoordinates(newCoordinates);

	std::cout << "Strafing: " << ((direction > 0) ? "Right" : "Left") << "\n";
	std::cout << "New Coordinates: (" << newCoordinates.GetX() << ", " << newCoordinates.GetY() << ", " << newCoordinates.GetZ() << ")\n";
}

Vector3D Player::calcSpeedVector()
{
	float yOrientation = degToRad(this->GetOrientation().GetY());
	float xOrientation = degToRad(this->GetOrientation().GetX());

	//Fly cam
	//float xComponent = sin(yOrientation) * cos(xOrientation);
	//float yComponent = -sin(xOrientation);
	//float zComponent = -cos(yOrientation) * cos(xOrientation);

	//Walking camera
	float xComponent = sin(yOrientation);
	float yComponent = 0;
	float zComponent = -cos(yOrientation);

	Vector3D speedVector = { xComponent, yComponent, zComponent };
	return speedVector;
}

float Player::Clamp(float value, float min, float max)
{
	if (value < min)
	{
		return min;
	}
	else if(value > max) {
		return max;
	}
	return value;
}

Solid* Player::Clone()
{
	return nullptr;
}

void Player::Render()
{
	CollisionHandler.Render();
}