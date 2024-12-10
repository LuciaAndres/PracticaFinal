#pragma once
#include "Teapot.h"
#include "Torus.h"
#include "Cube.h"
#include "Cuboid.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Emmiter.h"
#include "Scene.h"
#include "Model.h"
#include "Player.h"
#include "ModelLoader.h"
#include "FirstPersonCamera.h"
#include <chrono>

using namespace std::chrono;

class Game
{
private:
	const double TIME_INCREMENT = 0.4;
	const long UPDATE_PERIOD = 10;

	milliseconds initialMilliseconds;
	long lastUpdatedTime;;

	Scene* activeScene;
	vector<Scene*> scenes;

	Player* player;

public:

	Game() : 
	activeScene(nullptr), initialMilliseconds(duration_cast<milliseconds>(system_clock::now().time_since_epoch())), lastUpdatedTime(0), player(nullptr){}
	



	//inline Cuboid GetCuboidMiddle() { return this->cuboidMiddle; }



	void Init();
	void Render();
	void Update();
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessMouseMovement(int x, int y);
	void ProcessMouseClick(int button, int state, int x, int y);

};