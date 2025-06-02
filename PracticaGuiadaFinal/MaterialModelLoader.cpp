#include "MaterialModelLoader.h"
void MaterialModelLoader::loadMaterials(string fileName)
{
	string materialName;
	string line;
	string fullFileName = this->GetModelsFolder() + fileName;
	ifstream materialFile(fullFileName);
	if (materialFile.is_open())
	{
		while (getline(materialFile, line)) {
			line = trim(line);
			if (line[0] == '#' || line.size() == 0)
				continue;
			if (line.find("newmtl") != string::npos) {
				vector<string> lineInfo = split(line);
				materialName = lineInfo[1];
				this->materials[materialName] = Material(this->GetModelsFolder());
			}
			else {
				this->materials[materialName].ParseLine(line);
			}
		}
		materialFile.close();
	}
	else
	{
		throw runtime_error("Error openning file: " + fullFileName + " in MaterialModelLoader::loadMaterials()");
	}
}
/*
MaterialTriangle MaterialModelLoader::parseObjMaterialTriangle(const std::string& line) {
	std::istringstream ss(line);
	std::string tag, v0str, v1str, v2str;
	ss >> tag >> v0str >> v1str >> v2str;

	auto parseVertex = [](const std::string& token) -> std::tuple<int, int, int> {
		size_t first = token.find('/');
		size_t second = token.find('/', first + 1);
		int vi = std::stoi(token.substr(0, first)) - 1;
		int vti = std::stoi(token.substr(first + 1, second - first - 1)) - 1;
		int vni = std::stoi(token.substr(second + 1)) - 1;
		return std::make_tuple(vi, vti, vni);
		};

	int v0i, vt0i, vn0i;
	int v1i, vt1i, vn1i;
	int v2i, vt2i, vn2i;

	std::tie(v0i, vt0i, vn0i) = parseVertex(v0str);
	std::tie(v1i, vt1i, vn1i) = parseVertex(v1str);
	std::tie(v2i, vt2i, vn2i) = parseVertex(v2str);

	// Get vertex positions
	Vector3D v0 = verts[v0i];
	Vector3D v1 = verts[v1i];
	Vector3D v2 = verts[v2i];

	// Get normals
	Vector3D n0 = normals[vn0i];
	Vector3D n1 = normals[vn1i];
	Vector3D n2 = normals[vn2i];

	// Optional: use UVs if needed
	// Vector2D uv0 = uvs[vt0i]; // Only if you store uvs

	// Assign material
	const Material& mat = materials[currentMaterial];
	MaterialTriangle triangle(v0, v1, v2, n0, n1, n2, mat);

	return triangle;
}
*/


void MaterialModelLoader::LoadModel(const string& filePath)
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
				//Si la línea comienza por mtllib, es la definición del archivo de materiales que se usa
					if (line.find("mtllib") != string::npos) {
						vector<string> lineInfo = split(line);
						this->loadMaterials(lineInfo[1]);
					}
					else if (line.find("usemtl") != string::npos) {
						vector<string> lineInfo = split(line);
						this->currentMaterial = lineInfo[1];
					}
					else if (line[0] == 'v' && line[1] == 'n') //ejemplo: vn 0.0000	0.3603 - 0.9328 = > normal
					{
					Vector3D normal = this->parseObjLineToVector3D(line);
					this->normals.push_back(normal);
					}
					else if (line[0] == 'v') //ejemplo: v -0.091741 0.641907 0.606832 = > vértice
					{
					Vector3D vertex = this->parseObjLineToVector3D(line);
					this->calcBoundaries(vertex);
					this->verts.push_back(vertex);
					}
					else if (line[0] == 'f') {
						std::cout << "Parsing face line: " << line << std::endl;
						MaterialTriangle triangle = this->parseObjMaterialTriangle(line);
						std::cout << "Vertices: "
							<< triangle.getCoords0() << ", "
							<< triangle.getCoords1() << ", "
							<< triangle.getCoords2() << std::endl;
						triangle.SetMaterial(this->materials[this->currentMaterial]);
						//this->materialModel.AddMaterialTriangle(this->center(triangle));
						this->materialModel.AddMaterialTriangle(triangle);
					}
					std::cout << "[BOUNDARIES] min: (" << minX << ", " << minY << ", " << minZ << ")\n";
					std::cout << "[BOUNDARIES] max: (" << maxX << ", " << maxY << ", " << maxZ << ")\n";
					std::cout << "[CENTER] (" << (minX + getWidth() / 2) << ", " << (minY + getHeight() / 2) << ", " << (minZ + getLength() / 2) << ")\n";
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
/*MaterialTriangle MaterialModelLoader::parseObjMaterialTriangle(const string& line)
{
	Triangle triangle = this->parseObjTriangle(line);
	MaterialTriangle materialTriangle(triangle);
	return materialTriangle;




}*/

MaterialTriangle MaterialModelLoader::parseObjMaterialTriangle(const std::string& line) {
	std::istringstream ss(line);
	std::string tag, v0str, v1str, v2str;
	ss >> tag >> v0str >> v1str >> v2str;

	auto parseVertex = [](const std::string& token) -> std::tuple<int, int, int> {
		int vi = -1, vti = -1, vni = -1;
		size_t first = token.find('/');
		size_t second = token.find('/', first + 1);

		try {
			if (first == std::string::npos) {
				vi = std::stoi(token) - 1;
			}
			else if (second == std::string::npos) {
				vi = std::stoi(token.substr(0, first)) - 1;
				vti = std::stoi(token.substr(first + 1)) - 1;
			}
			else if (second == first + 1) {
				vi = std::stoi(token.substr(0, first)) - 1;
				vni = std::stoi(token.substr(second + 1)) - 1;
			}
			else {
				vi = std::stoi(token.substr(0, first)) - 1;
				vti = std::stoi(token.substr(first + 1, second - first - 1)) - 1;
				vni = std::stoi(token.substr(second + 1)) - 1;
			}
		}
		catch (...) {
			std::cerr << "Error al parsear token: " << token << std::endl;
		}

		return std::make_tuple(vi, vti, vni);
		};

	int v0i, vt0i, vn0i;
	int v1i, vt1i, vn1i;
	int v2i, vt2i, vn2i;

	std::tie(v0i, vt0i, vn0i) = parseVertex(v0str);
	std::tie(v1i, vt1i, vn1i) = parseVertex(v1str);
	std::tie(v2i, vt2i, vn2i) = parseVertex(v2str);

	if (v0i < 0 || v1i < 0 || v2i < 0 ||
		v0i >= verts.size() || v1i >= verts.size() || v2i >= verts.size()) {
		throw std::runtime_error("Índice de vértice fuera de rango en línea: " + line);
	}

	Vector3D v0 = verts[v0i];
	Vector3D v1 = verts[v1i];
	Vector3D v2 = verts[v2i];

	Vector3D n0 = (vn0i >= 0 && vn0i < normals.size()) ? normals[vn0i] : Vector3D();
	Vector3D n1 = (vn1i >= 0 && vn1i < normals.size()) ? normals[vn1i] : Vector3D();
	Vector3D n2 = (vn2i >= 0 && vn2i < normals.size()) ? normals[vn2i] : Vector3D();

	Material mat;
	if (materials.find(currentMaterial) != materials.end()) {
		mat = materials[currentMaterial];
	}

	return MaterialTriangle(v0, v1, v2, n0, n1, n2, mat);
}



MaterialTriangle MaterialModelLoader::center(MaterialTriangle triangle)
{
	Vector3D modelCenter(
		this->minX + this->getWidth() / 2.0,
		this->minY + this->getHeight() / 2.0,
		this->minZ + this->getLength() / 2.0);

	MaterialTriangle centeredTriangle(
		triangle.getCoords0() - modelCenter,
		triangle.getCoords1() - modelCenter,
		triangle.getCoords2() - modelCenter,
		triangle.getNormal0(),
		triangle.getNormal1(),
		triangle.getNormal2());

	centeredTriangle.SetMaterial(triangle.GetMaterial());
	return centeredTriangle;
}
void MaterialModelLoader::Clear()
{
	this->verts.clear();
	this->normals.clear();
	this->maxX = 0;
	this->maxY = 0;
	this->maxZ = 0;
	this->minX = 0;
	this->minY = 0;
	this->minZ = 0;
	this->materialModel.Clear();
}
