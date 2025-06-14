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
#include "MeshCollider.h"
#include "Player.h"
#include "MaterialModelLoader.h"
#include "FirstPersonCamera.h"
#include <chrono>

using namespace std::chrono;

class Game
{
private:
	const double TIME_INCREMENT = 0.016;
	const long UPDATE_PERIOD = 0.016;

	milliseconds initialMilliseconds;
	long lastUpdatedTime;;

	Scene* activeScene;
	vector<Scene*> scenes;

	Model* ammoBox;
	Player* player;

	UI ui;
public:

	Game() :
	activeScene(nullptr), initialMilliseconds(duration_cast<milliseconds>(system_clock::now().time_since_epoch())), lastUpdatedTime(0), player(nullptr), ammoBox(nullptr){}

	void Init();
	void Render();
	void Update();
	void ProcessMouseMovement(int x, int y);
	void ProcessMouseClick(int button, int state, int x, int y);
	void ProcessKeyPressed(unsigned char key, int px, int py);
	void ProcessKeyReleased(unsigned char key, int px, int py);
};