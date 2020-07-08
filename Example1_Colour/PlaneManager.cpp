#include "PlaneManager.h"

PlaneManager::PlaneManager(ID3D11Device* device, ID3D11DeviceContext* deviceContext, TextureManager* textrManager)
{
	rendererDevice = device;
	rendererDeviceContext = deviceContext;
	textureManager = textrManager;

	InitTileDesc();

	InitA();
}

PlaneManager::~PlaneManager()
{
	if (planeCentre)
	{
		delete planeCentre;
		planeCentre = 0;
	}

	if (planeNorth)
	{
		delete planeNorth;
		planeNorth = 0;
	}

	if (planeNorthEast)
	{
		delete planeNorthEast;
		planeNorthEast = 0;
	}

	if (planeEast)
	{
		delete planeEast;
		planeEast = 0;
	}

	if (planeSouthEast)
	{
		delete planeSouthEast;
		planeSouthEast = 0;
	}

	if (planeSouth)
	{
		delete planeSouth;
		planeSouth = 0;
	}
	if (planeSouthWest)
	{
		delete planeSouthWest;
		planeSouthWest = 0;
	}
	if (planeWest)
	{
		delete planeWest;
		planeWest = 0;
	}
	if (planeNorthWest)
	{
		delete planeNorthWest;
		planeNorthWest = 0;
	}
	if (planeNorthNorth)
	{
		delete planeNorthNorth;
		planeNorthNorth = 0;
	}
	if (planeNorthNorthWest)
	{
		delete planeNorthNorthWest;
		planeNorthNorthWest = 0;
	}
	if (planeNorthNorthEast)
	{
		delete planeNorthNorthEast;
		planeNorthNorthEast = 0;
	}
	if (planeSouthSouth)
	{
		delete planeSouthSouth;
		planeSouthSouth = 0;
	}
	if (planeSouthSouthWest)
	{
		delete planeSouthSouthWest;
		planeSouthSouthWest = 0;
	}
	if (planeSouthSouthEast)
	{
		delete planeSouthSouthEast;
		planeSouthSouthEast = 0;
	}
}

//Initialise all the tile descriptions
void PlaneManager::InitTileDesc()
{
	north.vertical = TileDesc::North;
	north.horizontal = TileDesc::NoneHor;

	south.vertical = TileDesc::South;
	south.horizontal = TileDesc::NoneHor;

	east.vertical = TileDesc::NoneVert;
	east.horizontal = TileDesc::East;

	west.vertical = TileDesc::NoneVert;
	west.horizontal = TileDesc::West;

	northWest.vertical = TileDesc::North;
	northWest.horizontal = TileDesc::West;

	northEast.vertical = TileDesc::North;
	northEast.horizontal = TileDesc::East;

	southWest.vertical = TileDesc::South;
	southWest.horizontal = TileDesc::West;

	southEast.vertical = TileDesc::South;
	southEast.horizontal = TileDesc::East;

	northNorth.vertical = TileDesc::NorthNorth;
	northNorth.horizontal = TileDesc::NoneHor;

	northNorthEast.vertical = TileDesc::NorthNorth;
	northNorthEast.horizontal = TileDesc::East;

	northNorthWest.vertical = TileDesc::NorthNorth;
	northNorthWest.horizontal = TileDesc::West;

	southSouth.vertical = TileDesc::SouthSouth;
	southSouth.horizontal = TileDesc::NoneHor;

	southSouthWest.vertical = TileDesc::SouthSouth;
	southSouthWest.horizontal = TileDesc::West;

	southSouthEast.vertical = TileDesc::SouthSouth;
	southSouthEast.horizontal = TileDesc::East;
}

//Init planes and push them to vector
void PlaneManager::InitA()
{
	//--- Init Planes
	planeNorth = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeEast = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeSouth = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeWest = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);

	planeNorthEast = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeNorthWest = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);

	planeSouthEast = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeSouthWest = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);

	planeNorthNorth = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeNorthNorthEast = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeNorthNorthWest = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);

	planeSouthSouth = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeSouthSouthWest = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);
	planeSouthSouthEast = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);

	//--Push to vector
	planeVector.push_back(planeNorth);
	planeVector.push_back(planeNorthEast);
	planeVector.push_back(planeEast);
	planeVector.push_back(planeSouthEast);
	planeVector.push_back(planeSouth);
	planeVector.push_back(planeSouthWest);
	planeVector.push_back(planeWest);
	planeVector.push_back(planeNorthWest);

	planeVector.push_back(planeNorthNorth);
	planeVector.push_back(planeNorthNorthWest);
	planeVector.push_back(planeNorthNorthEast);

	planeVector.push_back(planeSouthSouth);
	planeVector.push_back(planeSouthSouthEast);
	planeVector.push_back(planeSouthSouthWest);

	//-- Init Tile Desc
	planeNorth->SetTile(north);
	planeSouth->SetTile(south);
	planeEast->SetTile(east);
	planeWest->SetTile(west);

	planeNorthWest->SetTile(northWest);
	planeNorthEast->SetTile(northEast);

	planeSouthEast->SetTile(southEast);
	planeSouthWest->SetTile(southWest);

	planeNorthNorth->SetTile(northNorth);
	planeNorthNorthWest->SetTile(northNorthWest);
	planeNorthNorthEast->SetTile(northNorthEast);

	planeSouthSouth->SetTile(southSouth);
	planeSouthSouthEast->SetTile(southSouthWest);
	planeSouthSouthWest->SetTile(southSouthEast);

}

void PlaneManager::SetFileQuality(std::string filePat, int demQual, int texQual)
{
	filePath = filePat;
	fileDemQuality = demQual;
	fileTextureQuality = texQual;


	demLoader.SetFilePath(filePath);
	demLoader.SetFileQuality(fileDemQuality);
}

XMFLOAT3 PlaneManager::GetStartCameraPos()
{
	return planeCentre->GetCentre();
}

void PlaneManager::InitPlanes()
{
	//-- Init Centre Tile
	tempBuffer.path = startTile;
	tempBuffer.vec = demLoader.OpenFile(tempBuffer.path);
	planeCentre = new DEMPlane(rendererDevice, rendererDeviceContext, textureManager, tempBuffer);

	planeVector.push_back(planeCentre);


	bufferList.push_back(tempBuffer);


	CalculateSurroundingPlanes();
}

void PlaneManager::CalculateSurroundingPlanes()
{
	//loop through vector
	for (auto &i : planeVector)
	{
		//If it isnt the centre plane
		if (i != planeCentre)
		{
			XMINT3 tempPath = planeCentre->GetPath();

			//Calculate the vertical part of the new path first
			tempPath.z += i->GetTile().vertical;

			if (i->GetTile().vertical > 0)
			{
				//Check if the new path went over the boundaries (0 - 10 - 20 etc) or (9 - 19 - 29)
				for (int j = 0; j < i->GetTile().vertical; j ++)
				{
					if ((tempPath.z - j) % 10 == 0)
					{
						tempPath.y += 1;
						tempPath.z -= 10;

						break;
					}
				}
			}
			else if (i->GetTile().vertical < 0)
			{
				for (int j = 1; j <= abs(i->GetTile().vertical); j++)
				{
					if ((tempPath.z + j) % 10 == 0)
					{
						tempPath.y -= 1;
						tempPath.z += 10;

						break;
					}
				}
			}

			//Add the horizontal part
			tempPath.z += i->GetTile().horizontal;

			//Check if it crossed the boundaries (0, 1, 2, 3 etc) or (90, 91, 92, 93 etc)
			if (i->GetTile().horizontal > 0)
			{
				if (tempPath.z >= 100)
				{
					tempPath.y += 10;
					tempPath.z -= 100;
				}
			}
			else if (i->GetTile().horizontal < 0)
			{
				if (tempPath.z < 0)
				{
					tempPath.y -= 10;
					tempPath.z += 100;
				}
			}


			tempBuffer.path = tempPath;

			//Check if the required vector isnt in bufferList
			auto it = std::find(bufferList.begin(), bufferList.end(), tempBuffer);
			if (it == bufferList.end())
			{
				//Load it in if it isnt
				tempBuffer.vec = demLoader.OpenFile(tempBuffer.path);

				bufferList.push_back(tempBuffer);
			}
			else
			{
				//Grab it if it is
				tempBuffer.vec = it->vec;
			}

			//Update plane to recalculate vertices
			i->UpdatePlane(rendererDevice, tempBuffer);
		}
	}
}

DEMPlane* PlaneManager::FindClosestPlane(XMFLOAT3 cameraPosition)
{
	float closestDist = 10000000000.0f;
	float dist = 0;
	DEMPlane* tempPlane = NULL;

	for (auto &i : planeVector)
	{
		XMVECTOR v1 = XMLoadFloat3(&i->GetCentre());
		XMVECTOR v2 = XMLoadFloat3(&cameraPosition);
		XMVECTOR sub = XMVectorSubtract(v1, v2);

		XMVECTOR length = XMVector3Length(sub);

		XMStoreFloat(&dist, length);

		if (abs(dist) < abs(closestDist))
		{
			closestDist = dist;
			tempPlane = i;
		}
	}

	return tempPlane;
}

std::vector<DEMPlane*> PlaneManager::UpdatePlanes(XMFLOAT3 cameraPosition)
{
	DEMPlane* closestPlane = FindClosestPlane(cameraPosition);

	MultiThreadLoad();

	if (closestPlane != planeCentre)
	{
		tempBuffer.vec = closestPlane->GetBuffer();
		tempBuffer.path = closestPlane->GetPath();

		planeCentre->UpdatePlane(rendererDevice, tempBuffer);

		CalculateSurroundingPlanes();
	}

	return planeVector;
}

void PlaneManager::MultiThreadLoad()
{
	//--- North
	XMINT3 northPath = planeCentre->GetPath();

	northPath.z += 3;
	if (northPath.z % 10 == 0 ||
		(northPath.z - 1) % 10 == 0 ||
		(northPath.z - 2) % 10 == 0)
	{
		northPath.y += 1;
		northPath.z -= 10;
	}

	tempBuffer.path = northPath;

	//If false -> ftr is not being used
	if (!ftr_N.valid())
	{
		// ==end() if not found
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_N = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, northPath);
		}
	}
	else
	{
		//Checks the status, if ready() then can call .get() to receive the result
		if (ftr_N.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(northPath, ftr_N.get()));
		}
	}

	//--- North East
	XMINT3 northEastPath = planeCentre->GetPath();

	northEastPath.z += 3;

	if (northEastPath.z % 10 == 0 ||
		(northEastPath.z - 1) % 10 == 0 ||
		(northEastPath.z - 2) % 10 == 0)
	{
		northEastPath.y += 1;
	}
	else
	{
		northEastPath.z += 10;
	}

	if (northEastPath.z >= 100)
	{
		northEastPath.y += 10;
		northEastPath.z -= 100;
	}

	tempBuffer.path = northEastPath;

	if (!ftr_NE.valid())
	{
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_NE = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, northEastPath);
		}
	}
	else
	{
		if (ftr_NE.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(northEastPath, ftr_NE.get()));
		}
	}

	//--- North West
	XMINT3 northWestPath = planeCentre->GetPath();

	northWestPath.z += 3;

	if (northWestPath.z % 10 == 0 ||
		(northWestPath.z - 1) % 10 == 0 ||
		(northEastPath.z - 2) % 10 == 0)
	{
		northWestPath.y += 1;
		northWestPath.z -= 20;
	}
	else
	{
		northWestPath.z -= 10;
	}

	if (northWestPath.z < 0)
	{
		northWestPath.y -= 10;
		northWestPath.z += 100;
	}

	tempBuffer.path = northWestPath;

	if (!ftr_NW.valid())
	{
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_NW = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, northWestPath);
		}
	}
	else
	{
		if (ftr_NW.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(northWestPath, ftr_NW.get()));
		}
	}

	//--- East
	XMINT3 eastPath = planeCentre->GetPath();

	eastPath.z += 20;

	if (eastPath.z >= 100)
	{
		eastPath.y += 10;
		eastPath.z -= 100;
	}

	tempBuffer.path = eastPath;

	if (!ftr_E.valid())
	{
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_E = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, eastPath);
		}
	}
	else
	{
		if (ftr_E.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(eastPath, ftr_E.get()));
		}
	}

	//--- East North
	XMINT3 eastNorthPath = planeCentre->GetPath();

	eastNorthPath.z += 20;

	if (eastNorthPath.z >= 100)
	{
		eastNorthPath.y += 10;
		eastNorthPath.z -= 100;
	}
	eastNorthPath.z += 1;

	if ((eastNorthPath.z) % 10 == 0)
	{
		eastNorthPath.y += 1;
		eastNorthPath.z -= 10;
	}

	tempBuffer.path = eastNorthPath;

	if (!ftr_EN.valid())
	{
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_EN = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, eastNorthPath);
		}
	}
	else
	{
		if (ftr_EN.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(eastNorthPath, ftr_EN.get()));
		}
	}

	//--- East South
	XMINT3 eastSouthPath = planeCentre->GetPath();

	eastSouthPath.z += 20;

	if (eastSouthPath.z >= 100)
	{
		eastSouthPath.y += 10;
		eastSouthPath.z -= 100;
	}

	if ((eastSouthPath.z) % 10 == 0)
	{
		eastSouthPath.y -= 1;
		eastSouthPath.z += 9;
	}
	else
	{
		eastSouthPath.z -= 1;
	}

	tempBuffer.path = eastSouthPath;

	if (!ftr_ES.valid())
	{
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_ES = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, eastSouthPath);
		}
	}
	else
	{
		if (ftr_ES.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(eastSouthPath, ftr_ES.get()));
		}
	}

	//--- West
	XMINT3 westPath = planeCentre->GetPath();

	westPath.z -= 20;

	if (westPath.z < 0)
	{
		westPath.y -= 10;
		westPath.z += 100;
	}

	tempBuffer.path = westPath;

	if (!ftr_W.valid())
	{
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_W = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, westPath);
		}
	}
	else
	{
		if (ftr_W.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(westPath, ftr_W.get()));
		}
	}

	//--- West North
	XMINT3 westNorthPath = planeCentre->GetPath();

	westNorthPath.z -= 20;

	if (westNorthPath.z < 0)
	{
		westNorthPath.y -= 10;
		westNorthPath.z += 100;
	}

	westNorthPath.z += 1;
	if (westNorthPath.z % 10 == 0)
	{
		westNorthPath.y += 1;
		westNorthPath.z -= 10;
	}

	tempBuffer.path = westNorthPath;

	if (!ftr_WN.valid())
	{
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_WN = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, westNorthPath);
		}
	}
	else
	{
		if (ftr_WN.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(westNorthPath, ftr_WN.get()));
		}
	}

	//--- West South
	XMINT3 westSouthPath = planeCentre->GetPath();

	westSouthPath.z -= 20;

	if (westSouthPath.z < 0)
	{
		westSouthPath.y -= 10;
		westSouthPath.z += 100;
	}

	if (westSouthPath.z % 10 == 0 || westSouthPath.z == 0)
	{
		westSouthPath.y -= 1;
		westSouthPath.z += 9;
	}
	else
	{
		westSouthPath.z -= 1;
	}
	

	tempBuffer.path = westSouthPath;

	if (!ftr_WS.valid())
	{
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_WS = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, westSouthPath);
		}
	}
	else
	{
		if (ftr_WS.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(westSouthPath, ftr_WS.get()));
		}
	}

	//--- South
	XMINT3 southPath = planeCentre->GetPath();

	southPath.z -= 3;
	if((southPath.z + 1) % 10 == 0 ||
		(southPath.z + 2) % 10 == 0 ||
		(southPath.z + 3) % 10 == 0)
	{
		southPath.y -= 1;
		southPath.z += 10;
	}

	tempBuffer.path = southPath;

	//If false -> ftr is not being used
	if (!ftr_S.valid())
	{
		// ==end() if not found
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_S = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, southPath);
		}
	}
	else
	{
		//Checks the status, if ready() then can call .get() to receive the result
		if (ftr_S.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(southPath, ftr_S.get()));
		}
	}

	//--- South East 
	XMINT3 southEastPath = planeCentre->GetPath();

	southEastPath.z -= 3;
	if ((southEastPath.z + 1) % 10 == 0 ||
		(southEastPath.z + 2) % 10 == 0 ||
		(southEastPath.z + 3) % 10 == 0)
	{
		southEastPath.y -= 1;
		southEastPath.z += 10;
	}

	southEastPath.z -= 10;
	if (southEastPath.z < 0)
	{
		southEastPath.y -= 10;
		southEastPath.z += 100;
	}

	tempBuffer.path = southEastPath;

	//If false -> ftr is not being used
	if (!ftr_SE.valid())
	{
		// ==end() if not found
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_SE = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, southEastPath);
		}
	}
	else
	{
		//Checks the status, if ready() then can call .get() to receive the result
		if (ftr_SE.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(southEastPath, ftr_SE.get()));
		}
	}

	//--- South West
	XMINT3 southWestPath = planeCentre->GetPath();

	southWestPath.z -= 3;
	if ((southWestPath.z + 1) % 10 == 0 ||
		(southWestPath.z + 2) % 10 == 0 ||
		(southWestPath.z + 2) % 10 == 0)
	{
		southWestPath.y -= 1;
		southWestPath.z += 10;
	}

	southWestPath.z += 10;
	if (southWestPath.z >= 100)
	{
		southWestPath.y += 10;
		southWestPath.z -= 100;
	}

	tempBuffer.path = southWestPath;

	//If false -> ftr is not being used
	if (!ftr_SW.valid())
	{
		// ==end() if not found
		if (std::find(bufferList.begin(), bufferList.end(), tempBuffer) == bufferList.end())
		{
			ftr_SW = std::async(std::launch::async, &LoadDEM::OpenFile, demLoader, southWestPath);
		}
	}
	else
	{
		//Checks the status, if ready() then can call .get() to receive the result
		if (ftr_SW.wait_for(std::chrono::seconds::duration(0)) == future_status::ready)
		{
			bufferList.push_back(Buffer(southWestPath, ftr_SW.get()));
		}
	}
}