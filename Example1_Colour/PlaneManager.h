#ifndef _PLANEMANAGER_H
#define _PLANEMANAGER_H

#include "DXF.h"
#include "texturemanager.h"
#include "Buffer.h"


#include "DEMPlane.h"
#include "LoadDEM.h"

#include <vector>
#include <future>





class PlaneManager
{
public:
	PlaneManager(ID3D11Device* device, ID3D11DeviceContext* deviceContext, TextureManager* textrManager);
	~PlaneManager();

	std::vector<DEMPlane*> UpdatePlanes(XMFLOAT3 cameraPosition);

	XMFLOAT3 GetStartCameraPos();

	void SetFileQuality(std::string filePat, int demQual, int texQual);

	void InitPlanes();

	//void ABC();

protected:

	void CalculateSurroundingPlanes();

	void MultiThreadLoad();


	DEMPlane* FindClosestPlane(XMFLOAT3 cameraPosition);

	void InitTileDesc();

	void InitA();

private:
	ID3D11Device* rendererDevice;
	ID3D11DeviceContext* rendererDeviceContext;
	TextureManager* textureManager;

	DEMPlane* planeCentre;

	DEMPlane* planeNorth;
	DEMPlane* planeSouth;
	DEMPlane* planeWest;
	DEMPlane* planeEast;

	DEMPlane* planeNorthWest;
	DEMPlane* planeNorthEast;

	DEMPlane* planeSouthWest;
	DEMPlane* planeSouthEast;

	DEMPlane* planeNorthNorth;
	DEMPlane* planeNorthNorthEast;
	DEMPlane* planeNorthNorthWest;

	DEMPlane* planeSouthSouth;
	DEMPlane* planeSouthSouthWest;
	DEMPlane* planeSouthSouthEast;

	LoadDEM demLoader;

	std::vector<float> tempDemBuffer;

	std::vector<Buffer> bufferList;

	std::vector<DEMPlane*> planeVector;

	std::vector<DEMPlane*> test;

	Buffer tempBuffer;


	int startPos = 0;

	bool firstInit = true;

	std::future<std::vector<float> > ftr_N;
	std::future<std::vector<float> > ftr_NE;
	std::future<std::vector<float> > ftr_NW;

	std::future<std::vector<float> > ftr_E;
	std::future<std::vector<float> > ftr_EN;
	std::future<std::vector<float> > ftr_ES;

	std::future<std::vector<float> > ftr_W;
	std::future<std::vector<float> > ftr_WN;
	std::future<std::vector<float> > ftr_WS;

	std::future<std::vector<float> > ftr_S;
	std::future<std::vector<float> > ftr_SE;
	std::future<std::vector<float> > ftr_SW;

	XMINT3 startTile = XMINT3(37, 43, 0);

	std::string filePath;
	int fileDemQuality;
	int fileTextureQuality;

	//--- Tile Desc---

	TileDesc north;
	TileDesc south;
	TileDesc east;
	TileDesc west;
	TileDesc northWest;
	TileDesc northEast;
	TileDesc southWest;
	TileDesc southEast;
	
	TileDesc northNorth;
	TileDesc northNorthEast;
	TileDesc northNorthWest;

	TileDesc southSouth;
	TileDesc southSouthEast;
	TileDesc southSouthWest;

};
#endif _PLANEMANAGER_H
