#ifndef _DEMPLANE_H
#define _DEMPLANE_H

#include "DXF.h"
#include <vector>
#include "texturemanager.h"
#include "Buffer.h"
#include <string>
#include <atlstr.h>
#include <sstream>
#include <cmath>

using namespace DirectX;

class DEMPlane : public BaseMesh
{
public:
	DEMPlane(ID3D11Device* device, ID3D11DeviceContext* deviceContext, TextureManager* texMgr, Buffer demBuffer);
	DEMPlane();
	~DEMPlane();

	virtual void sendData(ID3D11DeviceContext* deviceContext, D3D_PRIMITIVE_TOPOLOGY top = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	std::vector<float> GetBuffer();

	void UpdatePlane(ID3D11Device* device, Buffer buff);

	void initBuffers(ID3D11Device* device);

	void SetPath(int hundred, int tenth, int km);
	void SetPath(XMINT3 path);
	XMINT3 GetPath();
	int GetHundredKM();
	int GetTenthKM();
	int GetOneKM();


	XMFLOAT3 GetCentre();

	void SetTextureMgr(TextureManager* texMgr);

	string GetTextureName();

	void SetTile(struct TileDesc);

	TileDesc GetTile();

private:
	void CalculateTexturePath();

protected:
	std::vector<float> floatBuffer;

	XMFLOAT3 centre;

	int demDimensions = 26;

	XMINT3 filePath;
	int hundredKM;
	int tenthKM;
	int oneKM;

	std::wstring folder_path;
	std::wstring hundred_path;
	std::wstring tenth_path;
	std::wstring one_path;

	std::wstring file_quality;

	stringstream texture_name;

	TextureManager* textureMgr;

	TileDesc tilePlane;
};
#endif
