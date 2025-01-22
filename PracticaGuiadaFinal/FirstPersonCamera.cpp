#include "FirstPersonCamera.h"
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0) 
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

void FirstPersonCamera::Render()
{
	glRotatef(this->GetOrientation().GetX(), 1, 0, 0);
	glRotatef(this->GetOrientation().GetY(), 0, 1, 0);
	glRotatef(this->GetOrientation().GetZ(), 0, 0, 1);
	glTranslatef(-1 * this->GetCoordinates().GetX(), -1 * this->GetCoordinates().GetY(), -1 * this->GetCoordinates().GetZ());

}

Vector3D FirstPersonCamera::calculateTextCoordinates()
{
    float yaw = degToRad(orientation.GetY());
    float pitch = degToRad(orientation.GetX());

    // Calculate forward, right, and up vectors
    Vector3D forward = Vector3D(
        cos(pitch) * sin(yaw),
        sin(pitch),
        cos(pitch) * cos(yaw)
    ).Normalize();

    Vector3D right = Vector3D(
        cos(yaw),
        0,
        -sin(yaw)
    ).Normalize();

    Vector3D up = forward.Cross(right).Normalize();

    // Debugging output
    std::cout << "Camera Position: " << coordinates << "\n";
    std::cout << "Forward: " << forward << ", Right: " << right << ", Up: " << up << "\n";

    // Calculate text position relative to the camera
    Vector3D textPosition = coordinates;
    textPosition = textPosition + (forward * 5.0f);  // Move forward
    std::cout << "After Forward Offset: " << textPosition << "\n";

    textPosition = textPosition + (right * 2.0f);   // Move to the right
    std::cout << "After Right Offset: " << textPosition << "\n";

    textPosition = textPosition + (up * 1.5f);      // Move upward
    std::cout << "After Up Offset: " << textPosition << "\n";

    // Return the calculated position (no inverted offsets)
    return textPosition;
}
void FirstPersonCamera::Update(const float& time)
{
	//const Vector3D& gravity = Vector3D(0, -9.81, 0);  
	//this->SetSpeed(this->calcSpeedVector());
	//Camera::Update(time, gravity);

}


Vector3D FirstPersonCamera::calcSpeedVector()
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
	float zComponent = -cos (yOrientation);
	
	Vector3D speedVector = { xComponent, yComponent, zComponent };
	return speedVector;
}
