#include "Guns.h"

void Guns::Trigger()
{
	auto now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	if (now - lastShotTime < fireRate || !bullet) return;

	Solid* newBullet = bullet->Clone();

	newBullet->SetCoordinates(outPos);
	newBullet->SetSpeed(direction * bulletSpeed);

	bullets.push_back(newBullet);
	lastShotTime = now;
}
 
void Guns::Update(const float& time) {
	for (auto& bullet : bullets)
	{
		bullet->Update(time, 0);
	}
}

void Guns::Render() {
	//render balas?
}