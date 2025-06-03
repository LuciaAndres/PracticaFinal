#include "Player.h"

bool Player::CheckCollision(Solid* other)
{
	return false;
}

void Player::Update(float deltaTime)
{
	this->UpdateMovement(deltaTime);
	this->UpdateCamera(deltaTime);
	this->ApplyGravity(deltaTime);

	OBB staticOBB(Vector3D(5, 3, 5), Vector3D(2.5, 5.0, 2.5), GetOrientationMatrix());
}

void Player::UpdateCamera(float deltaTime)
{
	this->view->SetCoordinates(this->GetCoordinates());
	this->view->SetOrientation(this->GetOrientation());
	this->view->Update(deltaTime);
}
void Player::UpdateMovement(float deltaTime)
{
	Vector3D originalPosition = GetCoordinates();

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
	if (keys['i'] || keys['I'])
	{
		this->MoveInDirectionDebug(1);
	}
	if (keys['k'] || keys['K'])
	{
		this->MoveInDirectionDebug(-1);
	}
	if (keys['j'] || keys['J'])
	{
		this->StrafeInDirectionDebug(-1);
	}
	if (keys['l'] || keys['L'])
	{
		this->StrafeInDirectionDebug(1);
	}
	if (keys['t'] || keys['T'])
	{
		Vector3D temp = this->GetCoordinates();
		temp.SetY(temp.GetY() + 1);
		this->SetCoordinates(temp);
	}
	if (keys['g'] || keys['G'])
	{
		Vector3D temp = this->GetCoordinates();
		temp.SetY(temp.GetY() - 1);
		this->SetCoordinates(temp);
	}
	if (keys[' '] && !isJumping)
	{
		isJumping = true;
		verticalSpeed = jumpHeight;
	}


	Vector3D newPosition = GetCoordinates();
	playerBoundingBox = OBB(newPosition + Vector3D(0, 1.25, 0), Vector3D(2.5, 2.5, 2.5), GetOrientationMatrix());

	bool onRamp = false;

	for (auto& ramp : scene->GetRamps()) {
		if (ramp->CheckCollision(playerBoundingBox)) {
			float rampHeight = ramp->GetRampHeightAt(newPosition);

			if (newPosition.GetY() < rampHeight) {
				newPosition.SetY(rampHeight);
				onRamp = true;
			}
		}
	}

	if (scene && scene->GetScenarioCollider()->CheckCollision(playerBoundingBox.ToAABB())) {
		SetCoordinates(originalPosition);
	}

	if (newPosition.GetY() < -30)
	{
		newPosition.SetY(0);
		SetCoordinates(Vector3D(0, 2.5, 0));
		isJumping = false;
		verticalSpeed = 0;
	}
}

void Player::ProcessMouseMovement(int x, int y)
{
	static bool firstMouse = true;

	int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
	int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

	int centerX = windowWidth / 2;
	int centerY = windowHeight / 2;

	if (!firstMouse)
	{
		float deltaX = x - centerX;
		float deltaY = y - centerY;

		float tempSensValue = 0.3f;

		Vector3D orientation = this->GetOrientation() + Vector3D(deltaY * SensValue, deltaX * SensValue, 0);

		orientation.SetX(Clamp(orientation.GetX(), -89.0f, 89.0f));

		this->SetOrientation(orientation);
	}

	firstMouse = false;

	glutWarpPointer(centerX, centerY);
}

void Player::ProcessMouseClick(int button, int state, int x, int y)
{
	if (button == 0)
	{
		
	}
}

void Player::MoveInDirection(float direction) {
	float yOrientation = degToRad(this->GetOrientation().GetY());

	float xComponent = sin(yOrientation) * direction;
	float zComponent = -cos(yOrientation) * direction;

	Vector3D movementVector(xComponent, 0, zComponent);

	movementVector = movementVector.Normalize();

	Vector3D newCoordinates = this->GetCoordinates() + movementVector * playerStep;

	this->SetCoordinates(newCoordinates);  // Update the player's position
}

void Player::MoveInDirectionDebug(float direction) {
	float yOrientation = degToRad(this->GetOrientation().GetY());

	float xComponent = sin(yOrientation) * direction;
	float zComponent = -cos(yOrientation) * direction;

	Vector3D movementVector(xComponent, 0, zComponent);

	movementVector = movementVector.Normalize();

	Vector3D newCoordinates = this->GetCoordinates() + movementVector * playerStep;
	this->view->SetCoordinates(newCoordinates);  // Update the player's position
}

void Player::StrafeInDirection(float direction)
{
	float yOrientation = degToRad(this->GetOrientation().GetY());

	float xComponent = cos(yOrientation) * direction;
	float zComponent = sin(yOrientation) * direction;

	Vector3D strafeVector(xComponent, 0, zComponent);

	strafeVector = strafeVector.Normalize();

	Vector3D newCoordinates = this->GetCoordinates() + strafeVector * playerStep;
	this->SetCoordinates(newCoordinates);
}

void Player::StrafeInDirectionDebug(float direction)
{
	float yOrientation = degToRad(this->GetOrientation().GetY());

	float xComponent = cos(yOrientation) * direction;
	float zComponent = sin(yOrientation) * direction;

	Vector3D strafeVector(xComponent, 0, zComponent);

	strafeVector = strafeVector.Normalize();

	Vector3D newCoordinates = this->GetCoordinates() + strafeVector * playerStep;
	this->view->SetCoordinates(newCoordinates);
}

float Player::Clamp(float value, float min, float max)
{
	if (value < min)
	{
		return min;
	}
	else if (value > max) {
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
	//Collider->Render();
	; // Green color for player's bounding box
	//playerBoundingBox.DebugRenderer(Color(0,1,0));
	//playerBoundingBox.ToAABB().DebugRenderer(Color(0, 1, 0));
	OBB staticOBB(Vector3D(5, 3, 5), Vector3D(2.5, 5.0, 2.5), GetOrientationMatrix());
	//staticOBB.DebugRenderer(Color(0, 1, 0));
}

void Player::ProcessKeyPressed(unsigned char key, int px, int py) {
	if (key == 27)
	{
		exit(0);
	}
	keys[key] = true;
}

void Player::ProcessKeyReleased(unsigned char key, int px, int py) {
	unsigned char lowerkey = tolower(key);
	unsigned char upperkey = toupper(key);

	keys[lowerkey] = false;
	keys[upperkey] = false;
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

void Player::ApplyGravity(float deltaTime) {
	if (isJumping) {
		verticalSpeed += gravity * deltaTime;
	}

	Vector3D currentPosition = GetCoordinates();
	Vector3D newPosition = currentPosition;
	newPosition.SetY(newPosition.GetY() + verticalSpeed * deltaTime);

	// Update OBB for the new position
	playerBoundingBox = OBB(newPosition + Vector3D(0, -2, 0), Vector3D(1.2, 3, 1.2), GetOrientationMatrix());
	/*std::cout << "[DEBUG] Creating OBB at: " << newPosition
         << " HalfSize: " << Vector3D(2.5, 5.0, 2.5)
          << " Orientation: " << GetOrientationMatrix() << std::endl;
		  */
	bool onGround = false;

	if (scene && scene->GetScenarioCollider()->CheckCollision(playerBoundingBox.ToAABB())) {
		if (verticalSpeed < 0) {
			newPosition.SetY(currentPosition.GetY());
			isJumping = false;
			verticalSpeed = 0.0f;
		}
		onGround = true;
	}

	for (auto& ramp : scene->GetRamps()) {
		if (ramp->CheckCollision(playerBoundingBox)) {
			float rampHeight = ramp->GetRampHeightAt(newPosition);

			if (newPosition.GetY() < rampHeight) {
				newPosition.SetY(rampHeight);
				isJumping = false;
				verticalSpeed = 0.0f;
				onGround = true;
			}
		}
	}

	if (!onGround) {
		isJumping = true;
	}

	SetCoordinates(newPosition);
}