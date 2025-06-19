#include "Menu.h"
void Menu::AddButton(const Button& button) {
	buttons.push_back(button);
}

void Menu::Render() const {
    glPushMatrix();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    for (const Button& button : buttons) {
        button.Render();
    }
    
    glPopMatrix(); // ModelView
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glPopMatrix();
}

void Menu::RenderCredits() const {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(1, 1, 1);
    glRasterPos2f(100, 300);
    const char* creditLine1 = "Creado por: Lucas Joglar, Hugo Garcia, Sergio Ponce y Lucia Andres";
    const char* creditLine2 = "Universidad URJC - 2025";
    const char* creditLine3 = "Engine Base proporcionada por Francisco Dominguez";
    const char* creditLine4 = "Presiona 'Volver' para regresar";

    for (const char* c = creditLine1; *c; ++c) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    glRasterPos2f(100, 270);
    for (const char* c = creditLine2; *c; ++c) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    glRasterPos2f(100, 240);
    for (const char* c = creditLine3; *c; ++c) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    glRasterPos2f(100, 210);
    for (const char* c = creditLine4; *c; ++c) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    };

void Menu::HandleClick(int x, int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    for (auto& button : buttons) {
        if (button.IsHovered(x, y, windowHeight)) {
            selectedScene = button.GetTargetScene();
            return;
        }
    }
}

void Menu::UpdateHoverState(int mouseX, int mouseY) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    for (auto& button : buttons) {
        bool hovered = button.IsHovered(mouseX, mouseY, windowHeight);
    }
}