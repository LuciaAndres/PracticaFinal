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
		this->view->Update(movementSpeed);
	}
	if (keys['s'] || keys['S']) {
		this->view->Update(-movementSpeed);
	}
	if (keys['a'] || keys['A']) {
		this->Strafe(-1);
	}
	if (keys['d'] || keys['D']) {
		this->Strafe(1);
	}
	if (keys['c'] || keys['C'])
	{
		std::cout << view->GetCoordinates().GetX() << ", " << view->GetCoordinates().GetY() << ", " << view->GetCoordinates().GetZ() << std::endl;
	}
}
/*
void Player::ProcessKeyPressed(unsigned char key, int px, int py)
{
	
	switch (key)
	{/*
	case 'w':
	case 'W':
		this->view->Update(playerStep);
		break;
	case 's':
	case 'S':
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
	case 'i':
	case 'I':
		this->view->SetCoordinates(Vector3D(GetCoordinates().GetX(), GetCoordinates().GetY() + 1, GetCoordinates().GetZ()));
		break;
	case 'k':
	case 'K':
		this->view->SetCoordinates(Vector3D(GetCoordinates().GetX(), GetCoordinates().GetY() - 1, GetCoordinates().GetZ()));
		break;
	case 27 :
		exit(0);
		break;
		
	default:
		std::cout << "Key Pressed: " << key << " is not valid" << std::endl;
		break;
	}
	updateColliderCoords();
}
*/
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
/*
// Move the player forward
void Player::MoveForward() {
	this->MoveInDirection(1);  // Move forward by passing 1
}

// Move the player backward
void Player::MoveBackward() {
	this->MoveInDirection(-1); // Move backward by passing -1
}

// Strafe the player to the left
void Player::StrafeLeft() {
	this->StrafeInDirection(-1);  // Strafe left by passing -1
}

// Strafe the player to the right
void Player::StrafeRight() {
	this->StrafeInDirection(1);   // Strafe right by passing 1
}

// General movement in forward or backward direction
void Player::MoveInDirection(float direction) {
	// Calculate movement vector based on player orientation
	float yOrientation = degToRad(this->view->GetOrientation().GetY());

	// Calculate forward/backward movement vector
	float xComponent = sin(yOrientation) * direction;
	float zComponent = -cos(yOrientation) * direction;

	Vector3D movementVector(xComponent, 0, zComponent);
	movementVector = movementVector.Normalize();  // Normalize to ensure consistent speed

	// Update speed but do not exceed MAX_SPEED
	playerStep = min(playerStep + 0.001f, MAX_SPEED);

	// Print the current speed for debugging
	std::cout << "Forward/Backward speed: " << playerStep << std::endl;

	// Calculate new coordinates by moving the player
	Vector3D newCoordinates = this->view->GetCoordinates() + movementVector * playerStep;
	this->view->SetCoordinates(newCoordinates);  // Update the player's position
}

// General strafing in left or right direction
void Player::StrafeInDirection(float direction) {
	// Calculate strafe vector based on player orientation
	float yOrientation = degToRad(this->view->GetOrientation().GetY());

	// Calculate left/right strafe vector
	float xComponent = cos(yOrientation) * direction;
	float zComponent = sin(yOrientation) * direction;

	Vector3D strafeVector(xComponent, 0, zComponent);
	strafeVector = strafeVector.Normalize();  // Normalize to ensure consistent speed

	// Update speed but do not exceed MAX_SPEED
	playerStep = min(playerStep + 0.001f, MAX_SPEED);

	// Print the current speed for debugging
	std::cout << "Strafe speed: " << playerStep << std::endl;

	// Calculate new coordinates by strafing the player
	Vector3D newCoordinates = this->view->GetCoordinates() + strafeVector * playerStep;
	this->view->SetCoordinates(newCoordinates);  // Update the player's position
}
*/
void Player::Strafe(float direction)
{
	float yOrientation = degToRad(this->view->GetOrientation().GetY());

	float xComponent = cos(yOrientation) * direction; 
	float zComponent = sin(yOrientation) * direction;

	Vector3D strafeVector(xComponent, 0, zComponent);

	strafeVector = strafeVector.Normalize();

	updateSpeed();

	std::cout << playerStep << std::endl;
	Vector3D newCoordinates = this->view->GetCoordinates() + strafeVector * playerStep;
	this->view->SetCoordinates(newCoordinates);
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
	
void Player::updateSpeed()
{

	playerStep = min(playerStep + 0.001f, MAX_SPEED);

}