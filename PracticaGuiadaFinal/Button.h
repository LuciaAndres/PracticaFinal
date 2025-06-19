#pragma once
#include "Vector3D.h"
#include "util.h"
#include <string>
#include <GL/glut.h>

using namespace std;
class Button
{
private:
    std::string label;
    Vector3D position;
    float width;
    float height;
    string targetScene;
public:
    Button(const string& text, const Vector3D& position, float width, float height, const string& sceneToGo) //le pasa una funcion en si
        : label(text), position(position), width(width), height(height), targetScene(sceneToGo) {}

    const std::string& GetTargetScene() const { return targetScene; }

    void Render() const;
    bool IsHovered(int mouseX, int mouseY, int windowHeight) const;
    void OnClick() const;
};

