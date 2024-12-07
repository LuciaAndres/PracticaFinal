#include "ModelLoader.h"

void ModelLoader::calcBoundaries(Vector3D vectorPoint)
{
	this->maxX = fmax(this->maxX, vectorPoint.GetX()); 
	this->maxY = fmax(this->maxY, vectorPoint.GetX());
	this->maxZ = fmax(this->maxZ, vectorPoint.GetX());
	this->minX = fmin(this->minX, vectorPoint.GetX()); 
	this->minY = fmin(this->minY, vectorPoint.GetY());
	this->minZ = fmin(this->minZ, vectorPoint.GetZ());
}

Triangle ModelLoader::center(Triangle triangle)
{
	Vector3D modelCenter(this->minX + this->getWidth() / 2.0,
		this->minY + this->getHeight() / 2.0,
		this->minZ + this->getLength() / 2);

	Triangle centeredTriangle(
		triangle.getCoords0() - modelCenter,
		triangle.getCoords1() - modelCenter,
		triangle.getCoords2() - modelCenter,
		triangle.getNormal0(),
		triangle.getNormal1(),
		triangle.getNormal2());

	return centeredTriangle;

}

Triangle ModelLoader::parseObjTriangle(const string& line)
{
	char c;
	int idxVertex0, idxVertex1, idxVertex2;
	int idxNormal0, idxNormal1, idxNormal2;

	istringstream stringStream(line);
	stringStream >> c;
	stringStream >> idxVertex0 >> c >> c >> idxNormal0;
	stringStream >> idxVertex1 >> c >> c >> idxNormal1;
	stringStream >> idxVertex2 >> c >> c >> idxNormal2;

	Vector3D vertex0 = this->verts[idxVertex0 - 1];
	Vector3D vertex1 = this->verts[idxVertex1 - 1];
	Vector3D vertex2 = this->verts[idxVertex2 - 1];
	Vector3D normal = this->normals[idxNormal0 - 1];

	Triangle parsedTriangle(vertex0, vertex1, vertex2, normal, normal, normal);

	return parsedTriangle;
}


Vector3D ModelLoader::parseObjLineToVector3D(const string& line)
{
	string typeOfPoint;
	float xCoordinate, yCoordinate, zCoordinate;
	istringstream stringStream(line);
	stringStream >> typeOfPoint >> xCoordinate >> yCoordinate >> zCoordinate;
	Vector3D vectorPoint(xCoordinate, yCoordinate, zCoordinate);
	return vectorPoint * this->getScale();
}


void ModelLoader::LoadModel(const std::string& filePath)
{
	try
	{
		ifstream objFile(filePath);
		if (objFile.is_open())
		{
			string line;
			int count = 0;
			while (getline(objFile, line))
			{
				if (line[0] == 'v' && line[1] == 'n') 
				{
					Vector3D normal = this->parseObjLineToVector3D(line);
					this->normals.push_back(normal);
				}
				else if (line[0] == 'v')
				{
					Vector3D vertex = this->parseObjLineToVector3D(line);
					this->calcBoundaries(vertex);
					this->verts.push_back(vertex);
				}
				else if (line[0] == 'f')
				{
					Triangle triangle = this->parseObjTriangle(line);
					this->model.AddTriangle(this->center(triangle));
					//this->model.AddTriangle(triangle);
				}
			}
			objFile.close();
		}
		else
		{
			cout << "No se ha podido abrir el archivo: " << filePath << endl;
		}
	}
	catch (exception& ex)
	{
		cout << "Excepción al procesar el archivo: " << filePath << endl; 
		cout << ex.what() << endl;
	}
}

void ModelLoader::Clear()
{
	this->verts.clear();
	this->normals.clear();
}