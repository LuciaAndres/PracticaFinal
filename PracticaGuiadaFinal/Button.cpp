#include "Button.h"
#include <GL/glut.h>

void Button::Render() const {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 0.1f, 0.1f);  // color botón
    glBegin(GL_QUADS);
    glVertex2f(position.GetX(), position.GetY());
    glVertex2f(position.GetX() + width, position.GetY());
    glVertex2f(position.GetX() + width, position.GetY() + height);
    glVertex2f(position.GetX(), position.GetY() + height);
    glEnd();


    // Contorno
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(position.GetX(), position.GetY());
    glVertex2f(position.GetX() + width, position.GetY());
    glVertex2f(position.GetX() + width, position.GetY() + height);
    glVertex2f(position.GetX(), position.GetY() + height);
    glEnd();

    // Texto
    float textWidth = label.size() * 9.0f;
    float textX = position.GetX() + (width - textWidth) / 2;
    float textY = position.GetY() + (height / 2) + 4.0f;

    glColor3f(1.0f, 1.0f, 1.0f);  // color texto
    glRasterPos2f(textX, textY);
    for (char c : label) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

bool Button::IsHovered(int mouseX, int mouseY, int windowHeight) const {
    return mouseX >= position.GetX() &&
        mouseX <= position.GetX() + width &&
        mouseY >= position.GetY() &&
        mouseY <= position.GetY() + height;
}

void Button::OnClick() const {
    
}