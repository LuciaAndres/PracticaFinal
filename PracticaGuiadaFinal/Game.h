#pragma once
#include "Teapot.h"
#include "Torus.h"
#include "Cube.h"
#include "Cuboid.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Emmiter.h"
#include "Scene.h"



class Game
{
private:

	Emmiter emmiter;
	Scene scene;

public:

	//Game() : {}
	



	//inline Cuboid GetCuboidMiddle() { return this->cuboidMiddle; }



	void Init();
	void Render();
	void Update();
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessMouseMovement(int x, int y);
	void ProcessMouseClick(int button, int state, int x, int y);

};