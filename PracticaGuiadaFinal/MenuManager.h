#pragma once
#include "Menu.h"
#include <unordered_map>
#include <string>

using namespace std;
class MenuManager
{
private:
	unordered_map<string, Menu> menus;
	string activeMenu;
	string lastSelection;
public:
	void AddMenu(const string& name, const Menu& menu);
	void SetActiveMenu(const string& name);
	void Render() const;
	void OnMouseClick(int x, int y);

	inline string GetCurrentSelection() const { return this->lastSelection; }
	inline string GetCurrentMenu() const { return this->activeMenu; }
	Menu& FindMenu(const string& name) {
		return menus.at(name);
	}
};

