#include "Game.h"
#include <iostream>

void Game::ProcessKeyPressed(unsigned char key, int px, int py)
{
	std::cout << "Tecla pulsada: " << key << std::endl;

	//GetCuboid().SetColor(Color()); LLAMA A UNA INSTANCIA

}

void Game::ProcessMouseMovement(int x, int y)
{
	std::cout << "Movimiento del mouse: " << x << ", " << y << std::endl;
}

void Game::ProcessMouseClick(int button, int state, int x, int y)
{
	std::cout << "Clic: " << button << std::endl;

}

void Game::Init()
{
	srand(static_cast<unsigned int>(std::time(nullptr)));
	
	Sphere SpherePrototype = Sphere();

	Teapot TeapotPrototype = Teapot(0.4);

	Cube CubePrototype = Cube(Vector3D(0,0,-2),Color(1,0,0),Vector3D(0,0,0),2);

	Teapot* tParticle = TeapotPrototype.Clone();

	Sphere* sParticle = SpherePrototype.Clone();

	Cube* cParticle = CubePrototype.Clone();
	
	emmiter.SetParticle(tParticle);

}

void Game::Render()
{
	scene.Render();
	emmiter.Render();
}

void Game::Update()
{
	emmiter.Update();
	scene.Update();
}