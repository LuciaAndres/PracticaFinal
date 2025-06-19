#pragma once
#include "util.h"
#include "Button.h"

using namespace std;

class Menu
{
private:
	string id = " ";
	vector<Button> buttons;
	string selectedScene = " ";
public:
	void AddButton(const Button& button);
	void Render() const;
	void HandleClick(int x, int y);
	void UpdateHoverState(int mouseX, int mouseY);
	string GetSelectedScene() const { return selectedScene; }
	void SetSelectedScene(const string& sceneToSet) { selectedScene = sceneToSet; }
	void SetSelectedId(const string& idToSet) { id = idToSet; }
	void RenderCredits() const;
};

