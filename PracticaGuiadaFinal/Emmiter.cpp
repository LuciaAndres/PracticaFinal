#include "Emmiter.h"
#include <iostream>

const double PI = 3.14159265358979;

void Emmiter::SetParticle(Solid* particle)
{
	config.setParticle(particle);
}

void Emmiter::AddParticle(Solid* particle)
{
	particles.push_back(particle);
}

void Emmiter::Render()
{
	for (auto& particle : particles)
	{
		particle->Render();
	}
}
void Emmiter::Update()
{
	Vector3D aux;
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	if ((currentTime.count() - initialMilliseconds.count()) - this->lastUpdateTime > this->config.getEmissionPeriod())
	{
		if(particles.size() < config.getParticleNum())
		{
			Solid* newParticle = config.getParticle()->Clone();

			newParticle->SetCoordinates(Vector3D(0, 0 , -2));
			newParticle->SetColor(randColor());
			newParticle->SetOrientation(randVecBinary());
			newParticle->SetOrientationSpeed(randVecBinary());
			newParticle->SetSpeed(particleSpeeds[current]);

			AddParticle(newParticle);
			current++;

		}
		lastUpdateTime = currentTime.count() - initialMilliseconds.count();
	}

	for (auto& particle : particles)
	{
		particle->Update();
		checkBoundary(particle);
	}

	int n = particles.size();
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (particles[i]->CheckCollision(particles[j]))
			{
				aux = particles[i]->GetSpeed();
				particles[i]->SetSpeed(particles[j]->GetSpeed());
				particles[j]->SetSpeed(aux);
			}
		}
	}
	
}

Emmiter* Emmiter::Clone()
{
	return new Emmiter(*this);
}

Vector3D randVecBinary()
{
	return Vector3D(rand() % 2, rand() % 2, rand() % 2);
}

Color randColor()
{
	return Color((rand() % 256) / 255.0f, (rand() % 256) / 255.0f, (rand() % 256) / 255.0f);
}

std::vector<Vector3D> Emmiter::circleSpeeds()
{
	int numParticles = config.getParticleNum();
	float angle = 2 * PI / config.getParticleNum();
	std::vector<Vector3D> speeds;
	 
	for (int i = 0; i < numParticles; i++)
	{
		float theta = i * angle;
		
		speeds.push_back(Vector3D(0.1 * cos(theta), 0.1 * sin(theta), 0));
	}

	return speeds;
}

void Emmiter::checkBoundary(Solid* object)
{
	Vector3D oSpeed = object->GetSpeed();

	float SpeedX = oSpeed.GetX();
	float SpeedY = oSpeed.GetY();
	float SpeedZ = oSpeed.GetZ();

	if (object->GetCoordinates().GetX() > boundary.GetX() || object->GetCoordinates().GetX() < -1 * boundary.GetX())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX * -1, SpeedY, SpeedZ);
		object->SetSpeed(nSpeed);
	}
	if (object->GetCoordinates().GetY() > boundary.GetY() || object->GetCoordinates().GetY() < -1 * boundary.GetY())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX, SpeedY * -1, SpeedZ);
		object->SetSpeed(nSpeed);
	}
	if (object->GetCoordinates().GetZ() > boundary.GetZ() || object->GetCoordinates().GetZ() < -1 * boundary.GetZ())
	{
		Vector3D oSpeed = object->GetSpeed();
		Vector3D nSpeed = Vector3D(SpeedX, SpeedY, SpeedZ * -1);
		object->SetSpeed(nSpeed);
	}
}

