////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <timeapi.h>


GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	for (int i = 0; i < models; i++)
	{
		m_Model[i] = 0;
	}

	m_Player = 0;
	//m_TextureShader = 0;
	m_LightShader = 0;
	m_Light = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 1.0f, -10.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);


		// Create the model object.
	for (int i = 0; i < models; i++)
	{
		m_Model[i] = new ModelClass;
		if (!m_Model[i])
		{
			return false;
		}
	}

	m_Player = new ModelClass;
	if (!m_Player)
	{
		return false;
	}
		
		// Initialize the model object
		//result = m_Model[i]->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), (char*)"../src/stone01.tga");

	result = m_Player->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), (char*)"../src/cube.txt", (char*)"../src/stone01.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[0]->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), (char*)"../src/cube.txt", (char*)"../src/stone01.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	result = m_Model[1]->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), (char*)"../src/cube.txt", (char*)"../src/crate.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	m_Player->CreateBoundingVolumes(m_Player->VertPosArray, m_Player->BoundingBoxVertPosArray, m_Player->BoundingSphere, m_Player->CenterOffset);
	m_Model[0]->CreateBoundingVolumes(m_Model[0]->VertPosArray, m_Model[0]->BoundingBoxVertPosArray, m_Model[0]->BoundingSphere, m_Model[0]->CenterOffset);
	m_Model[1]->CreateBoundingVolumes(m_Model[1]->VertPosArray, m_Model[1]->BoundingBoxVertPosArray, m_Model[1]->BoundingSphere, m_Model[1]->CenterOffset);

	//// Create the texture shader object.
	//m_TextureShader = new TextureShaderClass;
	//if (!m_TextureShader)
	//{
	//	return false;
	//}

	//// Initialize the color shader object.
	//result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	//if (!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, -1.0f, 1.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	//// Release the texture shader object.
	//if (m_TextureShader)
	//{
	//	m_TextureShader->Shutdown();
	//	delete m_TextureShader;
	//	m_TextureShader = 0;
	//}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.

	for (int i = 0; i < models; i++)
	{
		if (m_Model[i])
		{
			m_Model[i]->Shutdown();
			delete m_Model[i];
			m_Model[i] = 0;
		}
	}

	if (m_Player)
	{
		m_Player->Shutdown();
		delete m_Player;
		m_Player = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;
	static float m_previousTime = 0.0f;
	static float m_delta = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.01f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	float current_time = (float)timeGetTime();
	m_delta = (current_time - m_previousTime) * 0.001f;
	m_previousTime = current_time;

	if (GetKeyState('W') & 0x8000)
	{
		m_Camera->SetSpeedForward(10 * m_delta);
	}
	if (GetKeyState('A') & 0x8000)
	{
		m_Camera->SetSpeedRight(-10 * m_delta);
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_Camera->SetSpeedRight(10 * m_delta);
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_Camera->SetSpeedForward(-10 * m_delta);
	}
	if (GetKeyState('R') & 0x8000)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y + 10 * m_delta, m_Camera->GetPosition().z);
	}
	if (GetKeyState('F') & 0x8000)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y - 10 * m_delta, m_Camera->GetPosition().z);
	}
	if (GetKeyState(VK_UP) & 0x8000)
	{
		cameraXrot = m_Camera->GetRotation().x - 60 * m_delta;
	}
	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		cameraXrot = m_Camera->GetRotation().x + 60 * m_delta;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		cameraYrot = m_Camera->GetRotation().y - 60 * m_delta;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		cameraYrot = m_Camera->GetRotation().y + 60 * m_delta;
	}

	m_Camera->SetRotation(cameraXrot, cameraYrot, cameraZrot);

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;
	m_Model[0]->SetInstanceCount(1);
	m_Model[1]->SetInstanceCount(1000);

	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.2f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	m_Player->AABBWorld = XMMatrixTranslation(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

	//D3D11_MAPPED_SUBRESOURCE resource;
	//m_Direct3D->GetDeviceContext()->Map(m_Model[0]->m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
	//memcpy(resource.pData, &m_Model[0]->vertexData, m_Model[0]->GetVertexBufferSize());
	//m_Direct3D->GetDeviceContext()->Unmap(m_Model[0]->m_vertexBuffer, 0);

	m_Player->CalculateAABB(m_Player->BoundingBoxVertPosArray, m_Player->AABBWorld, m_Player->BoundingBoxMinVertex, m_Player->BoundingBoxMaxVertex);
	m_Model[0]->CalculateAABB(m_Model[0]->BoundingBoxVertPosArray, m_Model[0]->AABBWorld, m_Model[0]->BoundingBoxMinVertex, m_Model[0]->BoundingBoxMaxVertex);

	m_Model[1]->CalculateAABB(m_Model[1]->BoundingBoxVertPosArray, m_Model[1]->AABBWorld, m_Model[1]->BoundingBoxMinVertex, m_Model[1]->BoundingBoxMaxVertex);
	if (m_Player->BoundingBoxCollision(m_Player->BoundingBoxMinVertex, m_Player->BoundingBoxMaxVertex, m_Player->AABBWorld,
		m_Model[1]->BoundingBoxMinVertex, m_Model[1]->BoundingBoxMaxVertex, m_Model[1]->AABBWorld))
	{
		printf("collision");
		//worldMatrix = XMMatrixRotationY(rotation);


	}
	else
	{
		printf("no collison");
	}

	// Rotate the world matrix by the rotation value so that the cube will spin.
	//worldMatrix = XMMatrixRotationY(rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.

	//result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model[0]->GetVertexCount(), m_Model[0]->GetInstanceCount(), m_Model[0]->AABBWorld, viewMatrix,
	//	projectionMatrix, m_Model[0]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());

	//result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model[1]->GetVertexCount(), m_Model[1]->GetInstanceCount(), worldMatrix, viewMatrix,
	//	projectionMatrix, m_Model[1]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	for (int i = 0; i < models; i++)
	{
		m_Model[i]->Render(m_Direct3D->GetDeviceContext());
	//	//worldMatrix = XMMatrixTranslation(0.0f, 0.0f, 5.0f * i) * XMMatrixRotationY(rotation);

		result = m_LightShader->Render(m_Direct3D->GetDeviceContext(), m_Model[i]->GetVertexCount(), m_Model[i]->GetInstanceCount(), m_Model[i]->AABBWorld, viewMatrix,
			projectionMatrix, m_Model[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());

	}

	if (!result)
	{
		return false;
	}


	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}