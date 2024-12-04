#pragma once
#include "Model.h"
#include "Vector3D.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class ModelLoader
{
private:

	float scale;
	Model model;
	vector<Vector3D> verts;
	vector<Vector3D> normals;
	float maxX = 0, maxY = 0, maxZ = 0, minX = 0, minY = 0, minZ = 0;

	inline float getWidth() const { return maxX - minY; }
	inline float getHeight() const { return maxY - minY; }
	inline float getLenght() const { return maxZ - minZ; }
	void calcBoundaries(Vector3D vectorPoint);
	Triangle center(Triangle triangle);
	Vector3D parseObjLineToVector3D(const string& line);
	Triangle parseObjTriangle(const string& line);

public:
	ModelLoader() :
		scale(1) {}

	inline Model getModel() const { return model; }
	inline float getScale() const { return scale; }
	
	inline void setScale(const float& scaleToSet) { scale = scaleToSet; }
	void LoadModel(const string& filePath);
	void Clear();
};

