// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "TextureShader.h"
#include "DEMPlane.h"
#include "PlaneManager.h"
#include "Buffer.h"
#include "LoadDEM.h"

#include <fstream>

#include <algorithm>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <Psapi.h>

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

	void InitScene();

	void RenderMenu();
	void RenderScene();

	XMMATRIX ProjectionMatrix(const float near_plane, const float far_plane, const float fov_horiz, const float fov_vert);

	DEMPlane* ClosestPlane();

	void HandleInput();

	void RecordFPS();

private:
	TextureShader* textureShader;

	float num = 0.0f;

	PlaneManager* planeManager;

	std::vector<DEMPlane*> planeVector;

	float movementSpeed;


	bool next = false;
	int demQuality = 0;
	int textureQuality = 0;
	char buffer[64] = "H:\\AirSafe2018\\preprocessed-data\\os";

	LoadDEM demLoader;

	bool wrongPath = false;

	std::ofstream fpsFile;

	float clock_timer = 0;
};

#endif