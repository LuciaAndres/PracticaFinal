#include "Game.h"
#include <iostream>

void Game::ProcessKeyPressed(unsigned char key, int px, int py)
{
	/*
	std::cout << "Tecla pulsada: " << key << std::endl;
	if (key == 'w')
	{
		this->player->SetSpeed(
			Vector3D(
				this->player->GetSpeed().GetX(),
				this->player->GetSpeed().GetY() + 0.01,
				this->player->GetSpeed().GetZ()));
	} 
	else if (key == 's')
	{
		this->player->SetSpeed(
			Vector3D(
				this->player->GetSpeed().GetX(),
				this->player->GetSpeed().GetY() - 0.01,
				this->player->GetSpeed().GetZ()));
	}
	else if (key == 'a')
	{
		this->player->SetSpeed(
			Vector3D(
				this->player->GetSpeed().GetX() - 0.01,
				this->player->GetSpeed().GetY(),
				this->player->GetSpeed().GetZ()));
	}
	else if (key == 'd')
	{
		this->player->SetSpeed(
			Vector3D(
				this->player->GetSpeed().GetX() + 0.01,
				this->player->GetSpeed().GetY(),
				this->player->GetSpeed().GetZ()));
	}*/
	this->player->ProcessKeyPressed(key, px, py);
}

void Game::ProcessMouseMovement(int x, int y)
{
	this->player->ProcessMouseMovement(x, y);
	//std::cout << "Movimiento del mouse: " << x << ", " << y << std::endl;
}

void Game::ProcessMouseClick(int button, int state, int x, int y)
{
	std::cout << "Clic: " << button << std::endl;
	
}

void Game::Init()
{
	player = new Player();
    FirstPersonCamera* view = player->getFPC();
	Scene* mainScene = new(nothrow) Scene(view);
	this->scenes.push_back(mainScene);
	this->activeScene = mainScene;

	ModelLoader* loader = new ModelLoader();

	Cuboid testCuboid = Cuboid(Vector3D(0, -2, 0), Color(0.8, 0.8, 0), Vector3D(0, 0, 0), 100, 0.1, 100);
	Sphere testSphere = Sphere();
	Solid* sphereTest = testSphere.Clone();
	Solid* cuboidTest = testCuboid.Clone();
	sphereTest->SetSpeed(Vector3D(0, 0, 0));
	mainScene->AddGameObject(sphereTest);
	mainScene->AddGameObject(cuboidTest);

	
	/*
	this->player = new Model();
	
	loader->LoadModel("..\\..\\3dModels\\player.obj");
	*this->player = loader->getModel();
	player->SetCoordinates(Vector3D(0, 0, 1));
	player->SetOrientation(Vector3D(15, 180, 0));
	player->SetSpeed(Vector3D(0.8, 0.8, 0.9));
	player->PaintColor(Color(0.8, 0.8, 0.9));
	mainScene->AddGameObject(player);

	Model* star = new Model();
	loader->LoadModel("..\\..\\3dModels\\star.obj");
	*star = loader->getModel();
	star->SetCoordinates(Vector3D(1, 1, 1));
	star->SetOrientation(Vector3D(30, -60, -10));
	star->SetOrientationSpeed(Vector3D(3, 2, 1));
	star->SetSpeed(Vector3D(0.01, 0.02, 0.03)); 
	star->PaintColor(Color(0.2, 0.5, 0.1));
	mainScene->AddGameObject(star);
	*/
	loader->Clear();
}

void Game::Render()
{
	this->activeScene->Render();
	this->player->Render();
}

void Game::Update()
{
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	if ((currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime > UPDATE_PERIOD)
	{
		this->activeScene->Update(TIME_INCREMENT);
		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
	}
}