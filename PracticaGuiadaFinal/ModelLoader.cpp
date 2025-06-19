#include "ModelLoader.h"

void ModelLoader::calcBoundaries(Vector3D vectorPoint)
{	
		this->maxX = fmax(this->maxX, vectorPoint.GetX());
		this->maxY = fmax(this->maxY, vectorPoint.GetY());
		this->maxZ = fmax(this->maxZ, vectorPoint.GetZ());

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
	Vector3D normal0 = this->normals[idxNormal0 - 1];
	Vector3D normal1 = this->normals[idxNormal1 - 1];
	Vector3D normal2 = this->normals[idxNormal2 - 1];
	Triangle parsedTriangle(vertex0, vertex1, vertex2, normal0, normal1, normal2);

	return parsedTriangle;
}


Vector3D ModelLoader::parseObjLineToVector3D(const string& line)
{
	string typeOfPoint;
	float xCoordinate, yCoordinate, zCoordinate;
	istringstream stringStream(line);
	stringStream >> typeOfPoint >> xCoordinate >> yCoordinate >> zCoordinate;
	Vector3D vectorPoint(xCoordinate, yCoordinate, zCoordinate);
	//cout << "Scale: " << this->getScale() << endl;
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
	this->model.clear();
	minX = maxX = minY = maxY = minZ = maxZ = 0;
	//cout << "Size: " << verts.size() << endl;
	//cout << "Size: " << normals.size() << endl;
}

void ModelLoader::RenderBoundingBox()
{
	glBegin(GL_LINES);

	// Front face
	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);

	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, maxY, minZ);

	glVertex3f(maxX, maxY, minZ);
	glVertex3f(minX, maxY, minZ);

	glVertex3f(minX, maxY, minZ);
	glVertex3f(minX, minY, minZ);

	glVertex3f(maxX, minY, maxZ);

	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, maxY, maxZ);

	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(minX, maxY, maxZ);

	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, minY, maxZ);

	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ);

	glVertex3f(maxX, minY, minZ);
	glVertex3f(maxX, minY, maxZ);

	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, maxY, maxZ);

	glVertex3f(minX, maxY, minZ);
	glVertex3f(minX, maxY, maxZ);

	glEnd();

	glPointSize(8.0f);              // Make the points big enough to see
	glColor3f(1.0f, 0.0f, 0.0f);    // Red color for corners
	glBegin(GL_POINTS);

	// Front face corners (Z = minZ)
	glVertex3f(minX, minY, minZ);   // bottom-left-front
	glVertex3f(maxX, minY, minZ);   // bottom-right-front
	glVertex3f(maxX, maxY, minZ);   // top-right-front
	glVertex3f(minX, maxY, minZ);   // top-left-front

	// Back face corners (Z = maxZ)
	glVertex3f(minX, minY, maxZ);   // bottom-left-back
	glVertex3f(maxX, minY, maxZ);   // bottom-right-back
	glVertex3f(maxX, maxY, maxZ);   // top-right-back
	glVertex3f(minX, maxY, maxZ);   // top-left-back


	glEnd();

	//cout << "Bounds: X(" << minX << ", " << maxX << "), Y(" << minY << ", " << maxY << "), Z(" << minZ << ", " << maxZ << ")\n";

}