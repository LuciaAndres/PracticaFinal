#pragma once
#include "Solid.h"
#include "util.h"

class Bullet : public Solid
{
	private:
		Vector3D direction;
		float speed;
		float lifetime;
		float age;
	public:
		Bullet();
		Bullet(const Vector3D& position, const Vector3D& direction, float speed, const Color& color);

		void Update(const float& time, const Vector3D& gravity) override;
		void Render() override;

		inline void SetLifetime(float time) { this->lifetime = time; }
		inline float GetLifetime() const { return lifetime; }
};

