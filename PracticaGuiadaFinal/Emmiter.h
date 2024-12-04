#pragma once

#include "Solid.h"
#include <chrono>
#include <iostream>
#include "EmmiterConfiguration.h"
#include <vector>
#include "Sphere.h"


using namespace std::chrono;



class Emmiter : public Solid
{
private:

	EmmiterConfiguration config;
	std::vector<Solid*> particles;
	milliseconds initialMilliseconds;
	long lastUpdateTime;
	Vector3D boundary = Vector3D(12, 8, 4);
	std::vector<Vector3D> circleSpeeds();
	std::vector<Vector3D> particleSpeeds = circleSpeeds();
	int current = 0;

	void checkBoundary(Solid* object);

public:


	Emmiter()
	{
		
		config = EmmiterConfiguration(),
		this->initialMilliseconds = duration_cast<milliseconds>(system_clock::now().time_since_epoch()),
		this->lastUpdateTime = 0;
		{}
	}
	
	Emmiter* Clone();

	void SetParticle(Solid* particle);
	void AddParticle(Solid* particle);
	void Update();
	void Render();

};

Color randColor();
Vector3D randVecBinary();
