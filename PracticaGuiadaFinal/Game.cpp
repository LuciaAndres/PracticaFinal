#include "Game.h"
#include <algorithm>
#include <random>
#include <iostream>


void Game::ProcessKeyPressed(unsigned char key, int px, int py)
{
	if(!isInMenu) this->player->ProcessKeyPressed(key, px, py);

}

void Game::ProcessMouseMovement(int x, int y)
{
	if (!isInMenu) this->player->ProcessMouseMovement(x, y);
	//std::cout << "Movimiento del mouse: " << x << ", " << y << std::endl;
}

void Game::ProcessMouseClick(int button, int state, int x, int y)
{
	std::cout << "Clic: " << button << " en " << x << ", " << y << std::endl;

	if (isInMenu)
	{
		menuManager.OnMouseClick(x, y);
		std::string selected = menuManager.GetCurrentSelection();
		cout << "Selected: " << selected << endl;

		if (selected == "game") {
			InitLevels();
			isInMenu = false;
		}
		else if (selected == "credits") {
			menuManager.FindMenu("main").SetSelectedScene(" ");
			menuManager.SetActiveMenu("credits");
		}
		else if (selected == "exit") {
			exit(0);
		}
		else if (selected == "main") {
			menuManager.FindMenu("credits").SetSelectedScene(" ");
			menuManager.SetActiveMenu("main");
		}
		return;
	}

	player->ProcessMouseClick(button, state, x, y);
}
void Game::Init()
{
	Menu mainMenu;
	float centerX = glutGet(GLUT_WINDOW_WIDTH) / 2.0f;
	float buttonWidth = 150;

	mainMenu.AddButton(Button("Jugar", Vector3D(centerX - buttonWidth / 2, 160, 0), buttonWidth, 50, "game"));
	mainMenu.AddButton(Button("Creditos", Vector3D(centerX - buttonWidth / 2, 230, 0), buttonWidth, 50, "credits"));
	mainMenu.AddButton(Button("Salir", Vector3D(centerX - buttonWidth / 2, 300, 0), buttonWidth, 50, "exit"));
	menuManager.AddMenu("main", mainMenu);
	menuManager.SetActiveMenu("main");
	isInMenu = true;

	Menu creditsMenu;
	creditsMenu.AddButton(Button("Volver", Vector3D(200, 400, 0), 150, 50, "main"));
	menuManager.AddMenu("credits", creditsMenu);
}

void Game::InitLevels()
{
	cout << "CARGANDO NIVELES PUEDE TARDAR UNOS SEGUNDOS EN CARGAR" << endl;
	//GLUT STUFF
	glutSetCursor(GLUT_CURSOR_NONE);
	const GLclampf RED = 0.2;
	const GLclampf GREEN = 0.4;
	const GLclampf BLUE = 0.8;
	const GLclampf ALPHA = 1.0;
	glClearColor(RED, GREEN, BLUE, ALPHA);

	//MAKING ML
	ModelLoader* loader = new ModelLoader();
	MaterialModelLoader* texLoader = new MaterialModelLoader(".\\3dModels\\", 1);

	//SETTING UP PLAYER
	player = new Player();
	FirstPersonCamera* view = player->getFPC();

	player->SetCoordinates(Vector3D(0, 10.5, 0));
	player->SetOrientation(Vector3D(0, 180, 0));

	//SETTING UP SCENES
	Scene* levelOne = new(nothrow) Scene(view);
	Scene* levelTwo = new(nothrow) Scene(view);

	this->scenes.push_back(levelOne);
	this->scenes.push_back(levelTwo);

	this->activeScene = levelOne;

	player->SetScene(levelOne);

	//SETTING UP LEVEL 1

	MaterialModel* scenarioMat = new MaterialModel();
	MeshCollider* scenarioCollider = new MeshCollider();
	texLoader->Clear();
	texLoader->setId(1); 

	texLoader->LoadModelMaterial(".\\3dModels\\n1.obj");
	*scenarioMat = texLoader->GetMaterialModel();
	scenarioMat->SetCoordinates(Vector3D(0, 80, 0));

	scenarioCollider->UpdatePosition(scenarioMat->GetCoordinates());
	scenarioCollider->GenerateBoundingBoxesFromTriangles(scenarioMat->GetTriangles());
	levelOne->SetScenarioCollider(std::unique_ptr<MeshCollider>(scenarioCollider));

	levelOne->AddGameObject(scenarioMat);

	//SETTING UP LEVEL 2

	MaterialModel* scenarioMatLevel2 = new MaterialModel();
	MeshCollider* scenarioColliderLevel2 = new MeshCollider();
	texLoader->Clear();
	texLoader->setId(2);

	texLoader->LoadModelMaterial(".\\3dModels\\n2.obj");
	*scenarioMatLevel2 = texLoader->GetMaterialModel();
	scenarioMatLevel2->SetCoordinates(Vector3D(0, 10, 0));

	scenarioColliderLevel2->UpdatePosition(scenarioMatLevel2->GetCoordinates());
	scenarioColliderLevel2->GenerateBoundingBoxesFromTriangles(scenarioMatLevel2->GetTriangles());
	levelTwo->SetScenarioCollider(std::unique_ptr<MeshCollider>(scenarioColliderLevel2));

	levelTwo->AddGameObject(scenarioMatLevel2);
	
	//COLLECTIBLES

	std::vector<Vector3D> spawnPointsLevel1;
	std::vector<Vector3D> spawnPointsLevel2;

	spawnPointsLevel1 = {
		Vector3D(-39, 5, -86), Vector3D(112, 5, -86), Vector3D(49, 5, 52),
		Vector3D(25, 5, 85),
	};

	spawnPointsLevel2 = {
		Vector3D(75, -6, -21), Vector3D(-82, -6, 29), Vector3D(45, -6, 31),
		Vector3D(4, -6, 75),
	};

	random_shuffle(spawnPointsLevel1.begin(), spawnPointsLevel1.end());
	random_shuffle(spawnPointsLevel2.begin(), spawnPointsLevel2.end());

	texLoader->Clear();
	texLoader->setId(3);

	MaterialModel* cog = new MaterialModel();
	MeshCollider* cogCollider = new MeshCollider();

	MaterialModel* puzzle = new MaterialModel();
	MeshCollider* puzzleCollider = new MeshCollider();

	texLoader->LoadModelMaterial(".\\3dModels\\puzzle.obj");
	*cog = texLoader->GetMaterialModel();
	texLoader->Clear();

	texLoader->LoadModelMaterial(".\\3dModels\\chapita.obj");
	*puzzle = texLoader->GetMaterialModel();
	MaterialModel* cog0 = cog->Clone();
	MaterialModel* cog1 = cog->Clone();
	MaterialModel* cog2 = cog->Clone();
	MaterialModel* pieza0 = puzzle->Clone();
	MaterialModel* pieza1 = puzzle->Clone();
	MaterialModel* pieza2 = puzzle->Clone();

	cog0->SetCoordinates(spawnPointsLevel1[0]);
	cog1->SetCoordinates(spawnPointsLevel1[1]);
	cog2->SetCoordinates(spawnPointsLevel1[2]);
	pieza0->SetCoordinates(spawnPointsLevel2[0]);
	pieza1->SetCoordinates(spawnPointsLevel2[1]);
	pieza2->SetCoordinates(spawnPointsLevel2[2]);

	cogCollider->UpdatePosition(cog0->GetCoordinates());
	cogCollider->GenerateBoundingBoxesFromTriangles(cog->GetTriangles());
	cog0->SetOBB(*cogCollider);
	cogCollider->UpdatePosition(cog1->GetCoordinates());
	cogCollider->GenerateBoundingBoxesFromTriangles(cog->GetTriangles());
	cog1->SetOBB(*cogCollider);
	cogCollider->UpdatePosition(cog2->GetCoordinates());
	cogCollider->GenerateBoundingBoxesFromTriangles(cog->GetTriangles());
	cog2->SetOBB(*cogCollider);
	cogCollider->UpdatePosition(pieza0->GetCoordinates());
	cogCollider->GenerateBoundingBoxesFromTriangles(puzzle->GetTriangles());
	pieza0->SetOBB(*cogCollider);
	cogCollider->UpdatePosition(pieza1->GetCoordinates());
	cogCollider->GenerateBoundingBoxesFromTriangles(puzzle->GetTriangles());
	pieza1->SetOBB(*cogCollider);
	cogCollider->UpdatePosition(pieza2->GetCoordinates());
	cogCollider->GenerateBoundingBoxesFromTriangles(puzzle->GetTriangles());
	pieza2->SetOBB(*cogCollider);

	levelOne->GetCollectibles().push_back(cog0);
	levelOne->GetCollectibles().push_back(cog1);
	levelOne->GetCollectibles().push_back(cog2);

	levelTwo->GetCollectibles().push_back(pieza0);
	levelTwo->GetCollectibles().push_back(pieza1);
	levelTwo->GetCollectibles().push_back(pieza2);

	levelOne->AddGameObject(cog0);
	levelOne->AddGameObject(cog1);
	levelOne->AddGameObject(cog2);

	levelTwo->AddGameObject(pieza0);
	levelTwo->AddGameObject(pieza1);
	levelTwo->AddGameObject(pieza2);
}

void Game::Render()
{
	if (isInMenu) {
		menuManager.Render();
		if (menuManager.GetCurrentMenu() == "credits")
		{
			menuManager.FindMenu("credits").RenderCredits();
		}
		return;
	}
	activeScene->Render();
	player->Render();
	ui.Render();

	for (MaterialModel* pickup : activeScene->GetCollectibles()) {
		if (!pickup->GetIsHidden()) {
			//pickup->GetOBB().RenderBoundingBoxes();

		}
	}
}

void Game::Update()
{
	if (isInMenu) return;

	milliseconds currentTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	float deltaTime = (currentTime.count() - initialMilliseconds.count()) - lastUpdatedTime;

	if (deltaTime > UPDATE_PERIOD)
	{
		double time = deltaTime / 1000.0;
		player->Update(time);
		activeScene->Update(time);
		ui.UpdateFPS(time);
		lastUpdatedTime = currentTime.count() - initialMilliseconds.count();

		for (MaterialModel* pickup : activeScene->GetCollectibles()) {
			if (pickup && !pickup->GetIsHidden()){
				if (pickup->GetOBB().CheckCollision(player->getBoundingBox().ToAABB())) {
					OnPickupCollected(pickup);
					break;
				}
			}
		}
	}
}

void Game::ProcessKeyReleased(unsigned char key, int px, int py) {
	if (!isInMenu) player->ProcessKeyReleased(key, px, py);
}

void Game::OnPickupCollected(MaterialModel* pickup) {
	pickup->SetIsHidden(true); 
	//cout << "Hidden: " << pickup->GetIsHidden() << endl;
	collectedItems++;
	ui.UpdateScore(ui.getScore() + 100);
	//cout << "[DEBUG] Pickup collected! Total: " << collectedItems << endl;

	if (collectedItems == 3) {
		currentLevel++;
		if (currentLevel >= scenes.size()) {
			cout << "Fin de juego" << endl << "Puntuacion guardada en puntuacion.txt";
			saveScore("puntuacion.txt");
			exit(0);

		}

		activeScene = scenes[currentLevel];
		player->SetScene(activeScene);
		player->SetCoordinates(Vector3D(0, 10.5, 0));
		player->SetOrientation(Vector3D(0, 180, 0));
		collectedItems = 0;  // Reset for next level
	}
	
}

void Game::saveScore(const string& nombreArchivo) {
	try {
		ofstream salida(nombreArchivo);
			if (!salida.is_open()) {
				throw runtime_error("No se pudo abrir el archivo.");
			}
			salida << "Puntuacion: " << ui.getScore() << endl;
		salida.close();
	}
	catch (const exception& e) {
		cerr << "Error al guardar en archivo: " << e.what() << endl;
	}
}