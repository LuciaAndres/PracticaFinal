#include "MenuManager.h"
void MenuManager::AddMenu(const string& name, const Menu& menu) {
    menus[name] = menu;
}

void MenuManager::SetActiveMenu(const string& name) {
    if (menus.find(name) != menus.end()) {
        activeMenu = name;
    }
}

void MenuManager::OnMouseClick(int x, int y) {
    auto it = menus.find(activeMenu);
    if (it != menus.end()) {
        it->second.UpdateHoverState(x, y);
        it->second.HandleClick(x, y);
        lastSelection = it->second.GetSelectedScene();
    }
}

void MenuManager::Render() const {
    auto it = menus.find(activeMenu);
    if (it != menus.end()) {
        it->second.Render(); // Llama al método Render() del menú activo
    }
}