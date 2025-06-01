#include "Game.h"
#include <iostream>

MaterialModelLoader* texLoader = new MaterialModelLoader(".\\3dModels\\", 3);

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
	this->player->ProcessMouseClick(button, state, x, y);
	//std::cout << "Clic: " << button << std::endl;
}

void Game::Init()
{
	ModelLoader* loader = new ModelLoader();

	player = new Player();
	FirstPersonCamera* view = player->getFPC();

	Scene* mainScene = new(nothrow) Scene(view);
	Scene* textureScenes = new(nothrow) Scene(view);
	this->scenes.push_back(mainScene);
	this->scenes.push_back(textureScenes);
	this->activeScene = mainScene;

	Cuboid testCuboid = Cuboid(Vector3D(0, -2.1, 0), Color(0.8, 0.8, 0), Vector3D(0, 0, 0), 1, 0.1, 1);
	Solid* cuboidTest = testCuboid.Clone();

	player->SetCoordinates(Vector3D(0, 10.5, 0));
	player->SetOrientation(Vector3D(0, 180, 0));
	player->SetScene(mainScene);

	Model* scenario = new Model("Scenario");
	ammoBox = new Model("Box");
	loader->setScale(0.07);
	loader->LoadModel(".\\3dModels\\plano.obj");
	*scenario = loader->getModel();
	//scenario->SetCoordinates(Vector3D(0, 10, 0));
	scenario->SetCoordinates(Vector3D(0, -2, 0));
	scenario->PaintColor(Color(1, 0, 0));
	scenario->SetIsStationary(true);

	MeshCollider* scenarioCollider = new MeshCollider();
	scenarioCollider->UpdatePosition(scenario->GetCoordinates());
	scenarioCollider->GenerateBoundingBoxesFromTriangles(scenario->GetTriangles()); // Generate boxes

	texLoader->Clear();
	loader->Clear();
	MaterialModel* test = new MaterialModel();
	MaterialModel* cube = new MaterialModel();
	texLoader->setId(1);
	texLoader->LoadModel(".\\3dModels\\Taxi.obj");
	*test = texLoader->GetMaterialModel();
	texLoader->Clear();
	texLoader->setId(2);
	//texLoader->LoadModel("..\\3dModels\\cubito.obj");
	*cube = texLoader->GetMaterialModel();
	cube->SetCoordinates(Vector3D(-20, 2, -20));
	test->SetCoordinates(Vector3D(10, 2, 10));
	mainScene->AddGameObject(test);
	//mainScene->AddGameObject(scenario);
	mainScene->AddGameObject(cube);
	mainScene->SetScenarioCollider(std::unique_ptr<MeshCollider>(scenarioCollider));

	loader->Clear();
	loader->setScale(0.15);
	loader->LoadModel(".\\3dModels\\ammo.obj");
	*ammoBox = loader->getModel();
	ammoBox->SetCoordinates(Vector3D(0, 1, 0));
	ammoBox->SetOrientation(Vector3D(0, 90, 0));
	ammoBox->PaintColor(Color(0, 0.6, 0));
	//mainScene->AddGameObject(ammoBox);
	cuboidTest->SetCoordinates(test->GetCoordinates()+ Vector3D(0, 2, 0));
	mainScene->AddGameObject(cuboidTest);

	
}

void Game::Render()
{
	//player->getCollisionHandler()->DebugRenderer();

	this->activeScene->Render();
	this->scenes[1]->Render();
	player->Render();
	ui.Render();
	//texLoader->RenderBoundingBox();
}

void Game::Update()
{
	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	float deltaTime = (currentTime.count() - this->initialMilliseconds.count()) - this->lastUpdatedTime;

	if (deltaTime > UPDATE_PERIOD)
	{
        ammoBox->SetOrientation(Vector3D(0, ammoBox->GetOrientation().GetY() + 1, 0));
		ammoBox->SetCoordinates(Vector3D(0, 1 + cos(deg2rad(ammoBox->GetOrientation().GetY())), 0));

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