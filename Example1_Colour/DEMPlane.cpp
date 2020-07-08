#include "DEMPlane.h"



DEMPlane::DEMPlane(ID3D11Device * device, ID3D11DeviceContext * deviceContext, TextureManager* texMgr, Buffer demBuffer)
{
	folder_path = { L"H:\\AirSafe2018\\preprocessed-data\\os" };

	file_quality = { L"-high.png" };
	//if (device != NULL && deviceContext != NULL)
	{
		floatBuffer = demBuffer.vec;

		SetPath(demBuffer.path);

		SetTextureMgr(texMgr);

		initBuffers(device);
	}
}

DEMPlane::DEMPlane()
{
	
}


DEMPlane::~DEMPlane()
{
	BaseMesh::~BaseMesh();
}

void DEMPlane::sendData(ID3D11DeviceContext * deviceContext, D3D_PRIMITIVE_TOPOLOGY top)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType_Texture);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(top);
}

void DEMPlane::initBuffers(ID3D11Device * device)
{
	demDimensions = sqrt(floatBuffer.size() / 3);

	//Number of vertices in a DEM
	//Low = 26x26 - 25 Quads in a row - 50 Triangles in a row
	vertexCount = demDimensions * demDimensions;

	//Number of indices = 3750 in low
	indexCount = ((demDimensions - 1) * (demDimensions - 1)) * 6;

	VertexType_Texture* vertices = new VertexType_Texture[vertexCount];
	unsigned long* indices = new unsigned long[indexCount];
	
	if (floatBuffer.size() > 0)
	{
		//Starting Y Texture Coordinate 
		float yTex = 1.0f;
		//Amount to add each loop
		double yTexAdd = 1.0f / (demDimensions - 1);

		//Starting X Texture Coordinate
		float xTex = 0.0f;
		//Amount to add each loop
		float xTexAdd = 1.0f / (demDimensions - 1);

		//Threshold for resetting the yTex to 1 and increasing xTex
		//Floats arent accurate, therefore funky math required
		float yTexThreshold = 0.0f;

		if (demDimensions == 26 || demDimensions == 51)
		{
			yTexThreshold = -0.01f;
		}
		else
		{
			yTexThreshold = -0.0000001f;
		}

		int centreThreshold = 0;

		if (demDimensions == 51 || demDimensions == 101)
		{
			centreThreshold = vertexCount / 2;
		}
		else
		{
			centreThreshold = (vertexCount / 2) + (demDimensions / 2);
		}

		//Loop through all vertices
		for (int i = 0; i < vertexCount; i++)
		{
			//ECEF Coordinates - (Y, Z, X)
			vertices[i].position = XMFLOAT3(floatBuffer[(i * 3) + 1], floatBuffer[(i * 3) + 2], floatBuffer[(i * 3)]);
			vertices[i].texture = XMFLOAT2(xTex, yTex);

			//https://docs.microsoft.com/en-us/windows/win32/direct3d9/texture-coordinates
			//(0.0f, 0.0f) located at top left of object
			//We start at bottom left (0.0f, 1.0f) :- y-coordinate starts at 1.0f and decreases to 0.0f, x-coordinate starts at 0.0f and increases every 26 i or when yTex resets to 1.0f
			yTex -= yTexAdd;

			//Floating point precision requires funky math, otherwise final 0.0f tex coord isn't computed
			if (yTex < (float)yTexThreshold)
			{
				yTex = 1.0f;

				xTex += xTexAdd;
			}

			//Get centre point
			//if (i == (vertexCount / 2) + (demDimensions / 2))
			if (i == centreThreshold)
			{
				centre = vertices[i].position;
			}
		}

		//Current row number (0 -> 25)
		int rowPos = 0;

		//Assign indices
		//Clockwise order - rowPos indicates bottom left of right-angled triangle, rowPos + 1 indicates top left, +demDimensions finds the right half of triangle (located in the next column)
		for (int i = 0; i < indexCount; i += 6)
		{
			indices[i] = rowPos + 1;
			indices[i + 1] = rowPos;
			indices[i + 2] = rowPos + demDimensions;

			indices[i + 3] = rowPos + 1;
			indices[i + 4] = rowPos + demDimensions;
			indices[i + 5] = rowPos + 1 + demDimensions;

			rowPos++;

			//Resets rowPos to 0 if it is divisible by 26 (26, 52, 78 etc.) 
			if ((rowPos + 1) % demDimensions == 0)
			{
				rowPos++;
			}
		}
	}


	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	D3D11_BUFFER_DESC vertexBufferDesc = { sizeof(VertexType_Texture) * vertexCount, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	vertexData = { vertices, 0 , 0 };
	device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

	D3D11_BUFFER_DESC indexBufferDesc = { sizeof(unsigned long) * indexCount, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0 };
	indexData = { indices, 0, 0 };
	device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
}

void DEMPlane::SetTile(TileDesc a)
{
	tilePlane = a;
}

TileDesc DEMPlane::GetTile()
{
	return tilePlane;
}

void DEMPlane::UpdatePlane(ID3D11Device* device, Buffer buff)
{
	floatBuffer = buff.vec;
	SetPath(buff.path);

	CalculateTexturePath();

	textureMgr->loadTexture(texture_name.str(), const_cast<WCHAR*>(folder_path.c_str()));

	initBuffers(device);
}

std::vector<float> DEMPlane::GetBuffer()
{
	return floatBuffer;
}

void DEMPlane::SetPath(int hundred, int tenth, int km)
{
	hundredKM = hundred;
	tenthKM = tenth;
	oneKM = km;

	filePath = XMINT3(hundred, tenth, km);
}

void DEMPlane::SetPath(XMINT3 path)
{
	hundredKM = path.x;
	tenthKM = path.y;
	oneKM = path.z;

	filePath = path;
}

XMINT3 DEMPlane::GetPath()
{
	return filePath;
}

int DEMPlane::GetHundredKM()
{
	return hundredKM;
}

int DEMPlane::GetTenthKM()
{
	return tenthKM;
}

int DEMPlane::GetOneKM()
{
	return oneKM;
}

XMFLOAT3 DEMPlane::GetCentre()
{
	return centre;
}

void DEMPlane::SetTextureMgr(TextureManager * texMgr)
{
	textureMgr = texMgr;

	CalculateTexturePath();

	textureMgr->loadTexture(texture_name.str(),  const_cast<WCHAR*>(folder_path.c_str()));
}

void DEMPlane::CalculateTexturePath()
{
	folder_path = { L"H:\\AirSafe2018\\preprocessed-data\\os" };

	file_quality = { L"-high.png" };

	hundred_path = { L"\\" };

	hundred_path += to_wstring(GetHundredKM());

	tenth_path = { L"\\" };

	tenth_path += to_wstring(GetTenthKM());

	if (GetOneKM() < 10)
	{
		one_path = { L"\\0" };
	}
	else
	{
		one_path = { L"\\" };
	}

	one_path += to_wstring(GetOneKM());

	folder_path += hundred_path;
	folder_path += tenth_path;
	folder_path += one_path;
	folder_path += file_quality;

	texture_name << GetHundredKM() << GetTenthKM() << GetOneKM();
}

string DEMPlane::GetTextureName()
{
	return texture_name.str();
}
