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

	ModelLoader* collisionLoader = new ModelLoader();
	ModelLoader* loader = new ModelLoader();
	ModelLoader* loaderT = new ModelLoader();

	Cuboid testCuboid = Cuboid(Vector3D(0, -2.1, 0), Color(0.8, 0.8, 0), Vector3D(0, 0, 0), 100, 0.1, 100);

	Sphere testSphere = Sphere();
	testSphere.SetCoordinates(Vector3D(0, 1, 0));
	testSphere.SetRadius(1);

	Solid* sphereTest = testSphere.Clone();
	Solid* cuboidTest = testCuboid.Clone();

	//mainScene->AddGameObject(sphereTest);
	//mainScene->AddGameObject(cuboidTest);
	//mainScene->AddHiddenObject(collider);

	player->SetCoordinates(Vector3D(0, 10.5, 0));
	player->SetOrientation(Vector3D(0, 180, 0));
	player->SetScene(mainScene);

	Model* scenario = new Model();
	enemy = new Model();
	loader->setScale(0.05);
	loader->LoadModel(".\\3dModels\\scene2.obj");

	*scenario = loader->getModel();
	scenario->SetCoordinates(Vector3D(0, 10, 0));
	scenario->PaintColor(Color(1, 0, 0));
	scenario->SetIsStationary(true);

	Model* collider = new Model();
	collisionLoader->setScale(0.05);
	collisionLoader->LoadModel(".\\3dModels\\ramp.obj");
	*collider = collisionLoader->getModel();

	MeshCollider* scenarioCollider = new MeshCollider();
	scenarioCollider->UpdatePosition(scenario->GetCoordinates());
	scenarioCollider->GenerateBoundingBoxesFromTriangles(scenario->GetTriangles()); // Generate boxes

	mainScene->AddGameObject(scenario);
	mainScene->SetScenarioCollider(std::unique_ptr<MeshCollider>(scenarioCollider));

	loader->Clear();
	loaderT->setScale(0.15);
	//loaderT->LoadModel(".\\3dModels\\enemigo.obj");
	loaderT->LoadModel(".\\3dModels\\ammo.obj");
	*enemy = loaderT->getModel();
	enemy->SetCoordinates(Vector3D(0, 1, 0));
	enemy->SetOrientation(Vector3D(0, 90, 0));
	//enemy->PaintColor(Color(1,0.6,0));
	enemy->PaintColor(Color(0, 0.6, 0));
	mainScene->AddGameObject(enemy);

	mainScene->AddRamp(Vector3D(3, -2, -3.4), Vector3D(6.4, 1.2, -9), Vector3D(4.7, -0.4, -6.2));

}

void Game::Render()
{
	//this->activeScene->Render();
	//player->getCollisionHandler()->DebugRenderer();
	this->activeScene->Render();
	ui.Render();
	player->Render();
}

void Game::Update()
{
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	float deltaTime = (currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime;

	if (deltaTime > UPDATE_PERIOD)
	{
        enemy->SetOrientation(Vector3D(0, enemy->GetOrientation().GetY() + 1, 0));
        enemy->SetCoordinates(Vector3D(0, 1 + cos(deg2rad(enemy->GetOrientation().GetY())), 0));

		double time = deltaTime / 1000;
		this->player->Update(time);
		this->activeScene->Update(time);
		ui.UpdateFPS(time);
		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
	}
}

void Game::ProcessKeyReleased(unsigned char key, int px, int py) {
	player->ProcessKeyReleased(key, px, py);
}