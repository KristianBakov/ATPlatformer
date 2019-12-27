////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>
using namespace DirectX;


////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX&);

	XMVECTOR GetCamRight();
	XMVECTOR GetCamForward();
	XMVECTOR GetCamUp();

	void SetSpeedForward(float);
	void SetSpeedRight(float);
	void SetSpeedUp(float);
	XMMATRIX m_viewMatrix;

private:

	XMVECTOR forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR upv = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMVECTOR Camforward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR Camright = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR Camup = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	
	float forwardspeed = 0.0f;
	float rightspeed = 0.0f;
	float upspeed = 0.0f;

	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
};

#endif