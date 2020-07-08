// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{
	textureShader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	// Create Mesh object and shader object
	textureShader = new TextureShader(renderer->getDevice(), hwnd);
}

void App1::InitScene()
{
	planeManager = new PlaneManager(renderer->getDevice(), renderer->getDeviceContext(), textureMgr);
	planeManager->SetFileQuality(buffer, demQuality, textureQuality);

	planeManager->InitPlanes();

	XMFLOAT3 camPos = planeManager->GetStartCameraPos();
	camera->setPosition(camPos.x, camPos.y, camPos.z);

	/*textureMgr->loadTexture("00-high", L"..\\..\\DEM Files\\00-high.png");
	textureMgr->loadTexture("01-high", L"..\\..\\DEM Files\\01-high.png");*/

	movementSpeed = 5.0f;
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.
	if (textureShader)
	{
		delete textureShader;
		textureShader = 0;
	}
	if (planeManager)
	{
		delete planeManager;
		planeManager = 0;
	}

	if (fpsFile.is_open())
	{
		fpsFile.close();
	}

}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}

	HandleInput();

	if (next)
	{
		if (!planeManager)
		{
			InitScene();
		}
		else
		{
			planeVector = planeManager->UpdatePlanes(camera->getPosition());

			if (clock() - clock_timer > 1000)
			{
				RecordFPS();

				clock_timer = clock();


			}
		}
	}
	
	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

void App1::HandleInput()
{

	//https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	//A Key
	if (input->isKeyDown(65))
	{
		camera->setPosition(camera->getPosition().x - movementSpeed, camera->getPosition().y, camera->getPosition().z);
	}
	//D Key
	if (input->isKeyDown(68))
	{
		camera->setPosition(camera->getPosition().x + movementSpeed, camera->getPosition().y, camera->getPosition().z);
	}
	//W Key
	if (input->isKeyDown(87))
	{
		camera->setPosition(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z - movementSpeed);
	}
	//S Key
	if (input->isKeyDown(83))
	{
		camera->setPosition(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z + movementSpeed);
	}
	//Q Key
	if (input->isKeyDown(69))
	{
		camera->setPosition(camera->getPosition().x, camera->getPosition().y - movementSpeed, camera->getPosition().z);
	}
	//E Key
	if (input->isKeyDown(81))
	{
		camera->setPosition(camera->getPosition().x, camera->getPosition().y + movementSpeed, camera->getPosition().z);
	}
}

bool App1::render()
{
	if (next)
	{
		RenderScene();
	}
	else
	{
		RenderMenu();
	}

	return true;
}

void App1::RenderScene()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, rhProjectionMatrix;

	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Generate the view matrix based on the camera's position.
	camera->update();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	worldMatrix = renderer->getWorldMatrix();
	viewMatrix = camera->getViewMatrix();

	//Build a right handed projection matrix
	rhProjectionMatrix = XMMatrixPerspectiveFovRH(1.39626f, 1184 / 636, 1, 10000.0f);

	//Loop through planeVector and render all planes
	for (auto &i : planeVector)
	{
		i->sendData(renderer->getDeviceContext());
		textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, rhProjectionMatrix, textureMgr->getTexture(i->GetTextureName()));
		//textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, rhProjectionMatrix, textureMgr->getTexture("00-high"));
		textureShader->render(renderer->getDeviceContext(), i->getIndexCount());
	}

	// Render GUI
	gui();

	renderer->endScene();
}

void App1::RenderMenu()
{
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	ImGui::Text("DEM Quality: "); ImGui::SameLine();

	if (ImGui::RadioButton("High", &demQuality, 0))
	{
		demQuality = 0;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Medium", &demQuality, 1))
	{
		demQuality = 1;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Low", &demQuality, 2))
	{
		demQuality = 2;
	}

	ImGui::Text("Texture Quality: "); ImGui::SameLine();

	if (ImGui::RadioButton("High Tex", &textureQuality, 0))
	{
		textureQuality = 0;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Medium Tex", &textureQuality, 1))
	{
		textureQuality = 1;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Low Tex", &textureQuality, 2))
	{
		textureQuality = 2;
	}

	ImGui::Text("DEM File Path: "); 

	//ImGui::SameLine;

	ImGui::InputText("", buffer, IM_ARRAYSIZE(buffer), ImGuiInputTextFlags_None);

	if (ImGui::Button("Continue"))
	{
		demLoader.SetFilePath(buffer);

		std::vector<float> s = demLoader.OpenFile(XMINT3(37, 43, 0));

		if (s.size() == 0)
		{
			wrongPath = true;
		}
		else
		{
			next = true;
		}

	}


	if (wrongPath)
	{
		ImGui::Text("Wrong file path. Make sure the file path points to the folder that contains the first numbered folders (07, 16, 17, 26 etc)");

		if(ImGui::Button("Continue With Local DEM Files"))
		{
			char localPath[64] = "..\\..\\DEM_Files";

			demLoader.SetFilePath(localPath);

			std::vector<float> s = demLoader.OpenFile(XMINT3(37, 43, 0));

			if (s.size() == 0)
			{
				ImGui::Text("FILES MISSING");
			}
			else
			{
				next = true;

				strcpy_s(buffer, 64, "..\\..\\DEM_Files");
			}
		}
	}



	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	renderer->endScene();

}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);
	ImGui::Text("Camera X: %f Y: %f Z: %f", camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);

	XMFLOAT4 cameraRot;
	XMStoreFloat4(&cameraRot, camera->getRotation());

	ImGui::Text("Camera Rotation X: %f Y: %f Z: %f", cameraRot.x, cameraRot.y, cameraRot.z);
	//ImGui::Text("Centre X: %f Y: %f Z: %f", centrePlane->GetCentre().x, centrePlane->GetCentre().y, centrePlane->GetCentre().z);
	if (ClosestPlane() != NULL)
	{
		ImGui::Text("Closest Centre: %i, %i, %i", ClosestPlane()->GetHundredKM(), ClosestPlane()->GetTenthKM(), ClosestPlane()->GetOneKM());
	}

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


//https://docs.microsoft.com/en-us/windows/win32/direct3d9/projection-transform
XMMATRIX App1::ProjectionMatrix(const float near_plane, const float far_plane, const float fov_horiz, const float fov_vert)
{
	float    h, w, Q;

	w = (float)1 / tan(fov_horiz*0.5);  // 1/tan(x) == cot(x)
	h = (float)1 / tan(fov_vert*0.5);   // 1/tan(x) == cot(x)
	Q = far_plane / (far_plane - near_plane);

	XMFLOAT4X4 ret;
	ZeroMemory(&ret, sizeof(ret));

	ret(0, 0) = w;
	ret(1, 1) = h;
	ret(2, 2) = Q;
	ret(3, 2) = -Q * near_plane;
	ret(2, 3) = 1;


	return XMLoadFloat4x4(&ret);
}

DEMPlane* App1::ClosestPlane()
{
	float closestDist = 10000000000.0f;
	float dist = 0;
	DEMPlane* p = NULL;

	///*for (auto &i : planeVector)
	//{
	//	dist = sqrt(pow((abs(i->GetCentre().x - camera->getPosition().x)), 2) + pow(abs((i->GetCentre().y - camera->getPosition().y)), 2) + pow(abs((i->GetCentre().z - camera->getPosition().z)), 2));
	//	if (dist < closestDist)
	//	{
	//		closestDist = dist;
	//		p = i;
	//	}
	//}*/

	//https://stackoverflow.com/questions/10291862/what-is-the-best-way-to-get-distance-between-2-points-with-directxmath
	for (auto &i : planeVector)
	{
		XMVECTOR v1 = XMLoadFloat3(&i->GetCentre());
		XMVECTOR v2 = XMLoadFloat3(&camera->getPosition());
		XMVECTOR sub = XMVectorSubtract(v1, v2);

		XMVECTOR length = XMVector3Length(sub);

		XMStoreFloat(&dist, length);

		if (abs(dist) < abs(closestDist))
		{
			closestDist = dist;
			p = i;
		}
	}
	

	return p;
}

void App1::RecordFPS()
{
	PROCESS_MEMORY_COUNTERS pmc;

	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

	if (!fpsFile.is_open())
	{
		fpsFile.open("FPS Benchmarks.csv", std::ios::out);
	}

	fpsFile << clock() / 1000 << "," << timer->getFPS() << "," << pmc.PagefileUsage / 1024 / 1024 << std::endl;
}
