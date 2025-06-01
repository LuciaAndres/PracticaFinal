#pragma once
#include "util.h"
#include "Solid.h"
#include "Bullet.h"
#include <chrono>

using namespace std::chrono;

class Guns
{
private:

	Solid* bullet;
	std::vector<Solid*> bullets;
	Vector3D direction;
	Vector3D outPos;
	float bulletSpeed = 1.0f;

    int fireRate;
	long lastShotTime = 0;

public:

    Guns();
    Guns(Solid* bullet, Vector3D direction, float bulletSpeed, Vector3D outPos, int fireRate)
        : bullet(bullet),
          direction(Vector3D(direction).Normalize()),
          outPos(outPos),
          bulletSpeed(bulletSpeed),
          fireRate(fireRate)
    {}

    inline void SetBulletTemplate(Solid* bullet) { this->bullet = bullet; }
    inline void SetFireRate(int milliseconds) { this->fireRate = milliseconds; }
    inline void SetMuzzlePosition(const Vector3D& pos) { this->outPos = pos; }
    inline void SetDirection(const Vector3D& dir) { this->direction = Vector3D(dir).Normalize(); }
    inline void SetBulletSpeed(float speed) { this->bulletSpeed = speed; }

    inline Solid* GetBulletTemplate() const { return this->bullet; }
    inline int GetFireRate() const { return this->fireRate; }
    inline Vector3D GetMuzzlePosition() const { return this->outPos; }
    inline Vector3D GetDirection() const { return this->direction; }
    inline float GetBulletSpeed() const { return this->bulletSpeed; }

    void Trigger();
    void Update(const float& time);
    void Render();
};

