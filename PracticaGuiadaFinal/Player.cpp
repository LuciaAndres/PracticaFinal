#include "Player.h"
#include <algorithm>

bool Player::CheckCollision(Solid* other)
{
	return Collider.CheckCollision(other);
}
void Player::UpdateMovement(float deltaTime)
{
	float movementSpeed = playerStep * deltaTime;

	if (keys['w'] || keys['W']) {
		this->MoveInDirection(1);
	}
	if (keys['s'] || keys['S']) {
		this->MoveInDirection(-1);
	}
	if (keys['a'] || keys['A']) {
		this->StrafeInDirection(-1);
	}
	if (keys['d'] || keys['D']) {
		this->StrafeInDirection(1);
	}
	if (keys['c'] || keys['C'])
	{
		std::cout << view->GetCoordinates().GetX() << ", " << view->GetCoordinates().GetY() << ", " << view->GetCoordinates().GetZ() << std::endl;
		std::cout << verticalSpeed << std::endl;
	}
	if (keys['u'] || keys['U'])
	{
		Vector3D temp = this->view->GetCoordinates();
		temp.SetY(5);
		this->view->SetCoordinates(temp);
	}
	if (keys[' '] && !isJumping)
	{
		isJumping = true;
		verticalSpeed = jumpHeight;
	}


	if(isJumping)
	{
		verticalSpeed += gravity * deltaTime;

		Vector3D currentPosition = this->view->GetCoordinates();
		currentPosition.SetY(currentPosition.GetY() + verticalSpeed * deltaTime);
		std::cout << verticalSpeed << ", " << deltaTime << std::endl;
		if (currentPosition.GetY() <= groundLevel) {
			currentPosition.SetY(groundLevel);  
			isJumping = false;   
			verticalSpeed = 0.0f; 
		}

		this->view->SetCoordinates(currentPosition);  
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

void Player::MoveInDirection(float direction) {

	float yOrientation = degToRad(this->view->GetOrientation().GetY());

	float xComponent = sin(yOrientation) * direction;
	float zComponent = -cos(yOrientation) * direction;

	Vector3D movementVector(xComponent, 0, zComponent);

	movementVector = movementVector.Normalize();

	Vector3D newCoordinates = this->view->GetCoordinates() + movementVector * playerStep;
	this->view->SetCoordinates(newCoordinates);  // Update the player's position
}

void Player::StrafeInDirection(float direction)
{
	float yOrientation = degToRad(this->view->GetOrientation().GetY());

	float xComponent = cos(yOrientation) * direction; 
	float zComponent = sin(yOrientation) * direction;

	Vector3D strafeVector(xComponent, 0, zComponent);

	strafeVector = strafeVector.Normalize();

	Vector3D newCoordinates = this->view->GetCoordinates() + strafeVector * playerStep;
	this->view->SetCoordinates(newCoordinates);
}

void Player::updateColliderCoords()
{
	this->Collider.SetCoordinates(Vector3D(this->view->GetCoordinates()));
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
	Collider.Render();
}

void Player::ProcessKeyPressed(unsigned char key, int px, int py) {
	if (key == 27)
	{
		exit(0);
	}
	keys[key] = true;
}

void Player::ProcessKeyReleased(unsigned char key, int px, int py) {
	keys[key] = false;
	switch (key)
	{
	case 'w':
	case 'W':
	case 's':
	case 'S':
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		// Reset speed or stop movement when key is released
		playerStep = INITIAL_SPEED;
		break;
	default:
		break;
	}
}
	
