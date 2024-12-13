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

	Cuboid testCuboid = Cuboid(Vector3D(0, -2.1, 0), Color(0.8, 0.8, 0), Vector3D(0, 0, 0), 100, 0.1, 100);

	Sphere testSphere = Sphere();
	testSphere.SetCoordinates(Vector3D(0, 1, 0));
	testSphere.SetRadius(1);

	Solid* sphereTest = testSphere.Clone();
	Solid* cuboidTest = testCuboid.Clone();

	mainScene->AddGameObject(sphereTest);
	//mainScene->AddGameObject(cuboidTest);
	//mainScene->AddHiddenObject(collider);
	
	/*
	this->player = new Model();
	
	loader->LoadModel("..\\..\\3dModels\\player.obj");
	*this->player = loader->getModel();
	player->SetCoordinates(Vector3D(0, 0, 1));
	player->SetOrientation(Vector3D(15, 180, 0));
	player->SetSpeed(Vector3D(0.8, 0.8, 0.9));
	player->PaintColor(Color(0.8, 0.8, 0.9));
	mainScene->AddGameObject(player);
	*/
	Model* scenario = new Model();
	//loader->LoadModel("..\\..\\3dModels\\soda.obj");
	loader->setScale(0.05);
	loader->LoadModel("C:\\Users\\lucas\\source\\repos\\PracticaFinalTest\\PracticaGuiadaFinal\\3dModels\\scene.obj");
	*scenario = loader->getModel();
	std::cout << loader->getMinY() << std::endl;
	scenario->SetCoordinates(Vector3D(0, 10, 0));
	scenario->PaintColor(Color(1,1,0));
	scenario->SetIsStationary(true);
	//mainScene->AddHiddenObject(scenario);

	Collider* collider = player->getCollisionHandler();
	mainScene->AddCollider(std::make_unique<CapsuleCollider>(*dynamic_cast<CapsuleCollider*>(collider)));

	Collider* scenarioCollider = scenario->CreateMeshColliderFromModel(*scenario);
	mainScene->AddCollider(std::make_unique<CapsuleCollider>(*dynamic_cast<CapsuleCollider*>(scenarioCollider)));
}

void Game::Render()
{
	this->activeScene->Render();
	player->getCollisionHandler()->DebugRenderer();
}

void Game::Update()
{

	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	float deltaTime = (currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime;

	if (deltaTime > UPDATE_PERIOD)
	{
		this->player->UpdateMovement(TIME_INCREMENT);
		this->activeScene->Update(TIME_INCREMENT);
		this->lastUpdatedTime = currentTime.count() - this->initialMilliseconds.count();
	}
}

void Game::ProcessKeyReleased(unsigned char key, int px, int py) {
	player->ProcessKeyReleased(key, px, py);
}