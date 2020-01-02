////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include "d3dclass.h"
using namespace DirectX;

#include <fstream>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};
	struct InstanceType
	{
		XMFLOAT3 position;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	VertexType* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc, instanceBufferDesc;

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();

	size_t GetVertexBufferSize();

	bool BoundingBoxCollision(XMVECTOR& firstObjBoundingBoxMinVertex,
		XMVECTOR& firstObjBoundingBoxMaxVertex,
		XMMATRIX& firstObjWorldSpace,
		XMVECTOR& secondObjBoundingBoxMinVertex,
		XMVECTOR& secondObjBoundingBoxMaxVertex,
		XMMATRIX& secondObjWorldSpace);

	void CalculateAABB(std::vector<XMFLOAT3> boundingBoxVerts,
		XMMATRIX& worldSpace,
		XMVECTOR& boundingBoxMin,
		XMVECTOR& boundingBoxMax);

	void CreateBoundingVolumes(std::vector<XMFLOAT3>& vertPosArray,    // The array containing our models vertex positions
		std::vector<XMFLOAT3>& boundingBoxVerts,                            // Array we want to store the bounding box's vertex positions
		float& boundingSphere,                                            // The float containing the radius of our bounding sphere
		XMVECTOR& objectCenterOffset);                                    // A vector containing the distance between the models actual center and (0, 0, 0) in model space

	void SetInstanceCount(int count_in);

	ID3D11ShaderResourceView* GetTexture();
	std::vector<XMFLOAT3> VertPosArray;
	std::vector<XMFLOAT3> BoundingBoxVertPosArray;
	XMVECTOR BoundingBoxMinVertex;
	float BoundingSphere = 0.0f;
	XMVECTOR CenterOffset;
	XMVECTOR BoundingBoxMaxVertex;
	XMMATRIX AABBWorld;
	XMMATRIX Rotation;
	XMMATRIX Scale;
	XMMATRIX Translation;
	XMVECTOR Dir;

	bool iscollided = false;
	bool isbutton = false;
	bool isfalling = false;

	D3D11_SUBRESOURCE_DATA vertexData, instanceData;

	ID3D11Buffer* m_vertexBuffer;

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	int m_vertexCount, m_indexCount;

	ID3D11Buffer* m_instanceBuffer;
	TextureClass* m_Texture;
	int m_instanceCount;
	ModelType* m_model;
};

#endif