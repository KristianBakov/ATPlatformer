////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	//m_indexBuffer = 0;
	m_instanceBuffer = 0;
	m_Texture = 0;
	m_model = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* modelFilename, char* textureFilename)
{
	bool result;


	// Load in the model data,
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{

	// Release the model texture.
	ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetVertexCount()
{
	return m_vertexCount;
}

size_t ModelClass::GetVertexBufferSize()
{
	return sizeof(VertexType) * m_vertexCount;
}


int ModelClass::GetInstanceCount()
{
	return m_instanceCount;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

void ModelClass::SetInstanceCount(int count_in)
{
	m_instanceCount = count_in;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	//VertexType* vertices;
	InstanceType* instances;
	//D3D11_BUFFER_DESC vertexBufferDesc, instanceBufferDesc;
	//D3D11_SUBRESOURCE_DATA vertexData, instanceData;
	//unsigned long* indices;
	//D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	//D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;


	//// Set the number of vertices in the vertex array.
	//m_vertexCount = 36;

	//// Set the number of indices in the index array.
	//m_indexCount = 36;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	//// Create the index array.
	//indices = new unsigned long[m_indexCount];
	//if(!indices)
	//{
	//	return false;
	//}

	// Load the vertex array and index array with data.
	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);

		//indices[i] = i;
	}
	//// Load the vertex array with data.
	//vertices[0].position = XMFLOAT3(-1.0f,  1.0f, - 1.0f);  // Bottom left.
	//vertices[0].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[1].position = XMFLOAT3(1.0f,  1.0f, - 1.0f);  // Top middle.
	//vertices[1].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[2].position = XMFLOAT3(-1.0f, - 1.0f, - 1.0f);  // Bottom right.
	//vertices[2].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[3].position = XMFLOAT3(-1.0f, - 1.0f, - 1.0f);  // Bottom left.
	//vertices[3].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[3].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[4].position = XMFLOAT3(1.0f,  1.0f, - 1.0f);  // Top middle.
	//vertices[4].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[4].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[5].position = XMFLOAT3(1.0f, - 1.0f, - 1.0f);  // Bottom right.
	//vertices[5].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[5].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[6].position = XMFLOAT3(1.0f,  1.0f, - 1.0f);  // Bottom left.
	//vertices[6].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[6].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[7].position = XMFLOAT3(1.0f,  1.0f,  1.0f);  // Top middle.
	//vertices[7].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[7].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[8].position = XMFLOAT3(1.0f, - 1.0f, - 1.0f);  // Bottom right.
	//vertices[8].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[8].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[9].position = XMFLOAT3(1.0f, - 1.0f, - 1.0f);  // Bottom left.
	//vertices[9].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[9].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[10].position = XMFLOAT3(1.0f,  1.0f,  1.0f);  // Top middle.
	//vertices[10].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[10].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[11].position = XMFLOAT3(1.0f, - 1.0f,  1.0f);  // Bottom right.
	//vertices[11].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[11].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[12].position = XMFLOAT3(1.0f,  1.0f,  1.0f);  // Bottom left.
	//vertices[12].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[12].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[13].position = XMFLOAT3(-1.0f,  1.0f,  1.0f);  // Top middle.
	//vertices[13].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[13].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[14].position = XMFLOAT3(1.0f, - 1.0f,  1.0f);  // Bottom right.
	//vertices[14].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[14].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[15].position = XMFLOAT3(1.0f, - 1.0f,  1.0f);  // Bottom left.
	//vertices[15].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[15].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[16].position = XMFLOAT3(-1.0f,  1.0f,  1.0f);  // Top middle.
	//vertices[16].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[16].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[17].position = XMFLOAT3(-1.0f, - 1.0f,  1.0f);  // Bottom right.
	//vertices[17].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[17].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[18].position = XMFLOAT3(-1.0f,  1.0f,  1.0f);  // Bottom left.
	//vertices[18].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[18].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[19].position = XMFLOAT3(-1.0f,  1.0f, - 1.0f);  // Top middle.
	//vertices[19].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[19].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[20].position = XMFLOAT3(-1.0f, - 1.0f,  1.0f);  // Bottom right.
	//vertices[20].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[21].position = XMFLOAT3(-1.0f, - 1.0f,  1.0f);  // Bottom left.
	//vertices[21].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[21].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[22].position = XMFLOAT3(-1.0f,  1.0f, - 1.0f);  // Top middle.
	//vertices[22].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[22].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[23].position = XMFLOAT3(-1.0f, - 1.0f, - 1.0f);  // Bottom right.
	//vertices[23].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[23].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[24].position = XMFLOAT3(-1.0f,  1.0f,  1.0f);  // Bottom left.
	//vertices[24].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[24].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[25].position = XMFLOAT3(1.0f,  1.0f,  1.0f);  // Top middle.
	//vertices[25].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[25].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[26].position = XMFLOAT3(-1.0f,  1.0f, - 1.0f);  // Bottom right.
	//vertices[26].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[26].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[27].position = XMFLOAT3(-1.0f,  1.0f, - 1.0f);  // Bottom left.
	//vertices[27].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[27].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[28].position = XMFLOAT3(1.0f,  1.0f,  1.0f);  // Top middle.
	//vertices[28].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[28].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[29].position = XMFLOAT3(1.0f,  1.0f, - 1.0f);  // Bottom right.
	//vertices[29].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[29].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[30].position = XMFLOAT3(-1.0f, - 1.0f, - 1.0f);  // Bottom left.
	//vertices[30].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[30].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[31].position = XMFLOAT3(1.0f, - 1.0f, - 1.0f);  // Top middle.
	//vertices[31].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[31].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[32].position = XMFLOAT3(-1.0f, - 1.0f,  1.0f);  // Bottom right.
	//vertices[32].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[32].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[33].position = XMFLOAT3(-1.0f, - 1.0f,  1.0f);  // Bottom left.
	//vertices[33].texture = XMFLOAT2(0.0f, 1.0f);
	////vertices[33].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[34].position = XMFLOAT3(1.0f, - 1.0f, - 1.0f);  // Top middle.
	//vertices[34].texture = XMFLOAT2(0.5f, 0.0f);
	////vertices[34].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//vertices[35].position = XMFLOAT3(1.0f, - 1.0f,  1.0f);  // Bottom right.
	//vertices[35].texture = XMFLOAT2(1.0f, 1.0f);
	////vertices[35].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	//// Load the index array with data.
	//indices[0] = 0;  // Bottom left.
	//indices[1] = 1;  // Top middle.
	//indices[2] = 2;  // Bottom right.
	//indices[3] = 3;  // Bottom left.
	//indices[4] = 4;  // Top middle.
	//indices[5] = 5;  // Bottom right.
	//indices[6] = 6;  // Bottom left.
	//indices[7] = 7;  // Top middle.
	//indices[8] = 8;  // Bottom right.
	//indices[9] = 9;  // Bottom left.
	//indices[10] = 10;  // Top middle.
	//indices[11] = 11;  // Bottom right.
	//indices[12] = 12;  // Bottom left.
	//indices[13] = 13;  // Top middle.
	//indices[14] = 14;  // Bottom right.
	//indices[15] = 15;  // Bottom left.
	//indices[16] = 16;  // Top middle.
	//indices[17] = 17;  // Bottom right.
	//indices[18] = 18;  // Bottom left.
	//indices[19] = 19;  // Top middle.
	//indices[20] = 20;  // Bottom right.
	//indices[21] = 21;  // Bottom left.
	//indices[22] = 22;  // Top middle.
	//indices[23] = 23;  // Bottom right.
	//indices[24] = 24;  // Bottom left.
	//indices[25] = 25;  // Top middle.
	//indices[26] = 26;  // Bottom right.
	//indices[27] = 27;  // Bottom left.
	//indices[28] = 28;  // Top middle.
	//indices[29] = 29;  // Bottom right.
	//indices[30] = 30;  // Bottom left.
	//indices[31] = 31;  // Top middle.
	//indices[32] = 32;  // Bottom left.
	//indices[33] = 33;  // Top middle.
	//indices[34] = 34;  // Bottom left.
	//indices[35] = 35;  // Top middle.


	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	

	//// Set up the description of the static index buffer.
 //   indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
 //   indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
 //   indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
 //   indexBufferDesc.CPUAccessFlags = 0;
 //   indexBufferDesc.MiscFlags = 0;
	//indexBufferDesc.StructureByteStride = 0;
	//// Give the subresource structure a pointer to the index data.
 //   indexData.pSysMem = indices;
	//indexData.SysMemPitch = 0;
	//indexData.SysMemSlicePitch = 0;
	//// Create the index buffer.
	//result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	//if(FAILED(result))
	//{
	//	return false;
	//}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	//delete [] indices;
	//indices = 0;

	// Set the number of instances in the array.
	m_instanceCount = 10;

	// Create the instance array.
	instances = new InstanceType[m_instanceCount];
	if (!instances)
	{
		return false;
	}

	AABBWorld = XMMatrixIdentity();

	//for (int i = 0; i < 100; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		int instance = i * 100 + j;
	//		instances[instance].position = XMFLOAT3(i * 2, 0.0f , j * 2);
	//	}
	//}
	//for (int i = 0; i < m_instanceCount; i++)
	//{
	//	instances[i].position = XMFLOAT3(i * 10, 0.0f, 0.0f);
	//}
		//instances[0].position = XMFLOAT3(0, 0, 0);
		//instances[1].position = XMFLOAT3(2, 2, 2);
		//instances[2].position = XMFLOAT3(3, 3, 3);
		//instances[3].position = XMFLOAT3(4, 4, 4);
		//instances[4].position = XMFLOAT3(5, 5, 5);
	//	instances[5].position = XMFLOAT3(6, 6, 6);

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				int instance = i * 10 + j + k;
				instances[instance].position = XMFLOAT3(i , j , k );
			}
		}
	}
	instances[0].position = XMFLOAT3(0, 0, 0);

	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the instance array now that the instance buffer has been created and loaded.
	delete[] instances;
	instances = 0;


	return true;
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}

void ModelClass::CreateBoundingVolumes(std::vector<XMFLOAT3>& vertPosArray,
	std::vector<XMFLOAT3>& boundingBoxVerts,
	float& boundingSphere,
	XMVECTOR& objectCenterOffset)
{
	XMFLOAT3 minVertex = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxVertex = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int i = 0; i < m_vertexCount; i++)
	{
		vertPosArray.push_back(XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z));
	}

	for (UINT i = 0; i < vertPosArray.size(); i++)
	{
		// The minVertex and maxVertex will most likely not be actual vertices in the model, but vertices
		// that use the smallest and largest x, y, and z values from the model to be sure ALL vertices are
		// covered by the bounding volume

		//Get the smallest vertex 
		minVertex.x = min(minVertex.x, vertPosArray[i].x);    // Find smallest x value in model
		minVertex.y = min(minVertex.y, vertPosArray[i].y);    // Find smallest y value in model
		minVertex.z = min(minVertex.z, vertPosArray[i].z);    // Find smallest z value in model

		//Get the largest vertex 
		maxVertex.x = max(maxVertex.x, vertPosArray[i].x);    // Find largest x value in model
		maxVertex.y = max(maxVertex.y, vertPosArray[i].y);    // Find largest y value in model
		maxVertex.z = max(maxVertex.z, vertPosArray[i].z);    // Find largest z value in model
	}

	// Compute distance between maxVertex and minVertex
	float distX = (maxVertex.x - minVertex.x) / 2.0f;
	float distY = (maxVertex.y - minVertex.y) / 2.0f;
	float distZ = (maxVertex.z - minVertex.z) / 2.0f;

	// Now store the distance between (0, 0, 0) in model space to the models real center
	objectCenterOffset = XMVectorSet(maxVertex.x - distX, maxVertex.y - distY, maxVertex.z - distZ, 0.0f);

	// Compute bounding sphere (distance between min and max bounding box vertices)
	// boundingSphere = sqrt(distX*distX + distY*distY + distZ*distZ) / 2.0f;
	boundingSphere = XMVectorGetX(XMVector3Length(XMVectorSet(distX, distY, distZ, 0.0f)));

	// Create bounding box    
	// Front Vertices
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, minVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, maxVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, maxVertex.y, minVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, minVertex.y, minVertex.z));

	// Back Vertices
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, minVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, minVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(maxVertex.x, maxVertex.y, maxVertex.z));
	boundingBoxVerts.push_back(XMFLOAT3(minVertex.x, maxVertex.y, maxVertex.z));
}

void ModelClass::CalculateAABB(std::vector<XMFLOAT3> boundingBoxVerts,
	XMMATRIX& worldSpace,
	XMVECTOR& boundingBoxMin,
	XMVECTOR& boundingBoxMax)
{
	XMFLOAT3 minVertex = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxVertex = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	//Loop through the 8 vertices describing the bounding box
	for (UINT i = 0; i < 8; i++)
	{
		//Transform the bounding boxes vertices to the objects world space
		XMVECTOR Vert = XMVectorSet(boundingBoxVerts[i].x, boundingBoxVerts[i].y, boundingBoxVerts[i].z, 0.0f);
		Vert = XMVector3TransformCoord(Vert, worldSpace);

		//Get the smallest vertex 
		minVertex.x = min(minVertex.x, XMVectorGetX(Vert));    // Find smallest x value in model
		minVertex.y = min(minVertex.y, XMVectorGetY(Vert));    // Find smallest y value in model
		minVertex.z = min(minVertex.z, XMVectorGetZ(Vert));    // Find smallest z value in model

		//Get the largest vertex 
		maxVertex.x = max(maxVertex.x, XMVectorGetX(Vert));    // Find largest x value in model
		maxVertex.y = max(maxVertex.y, XMVectorGetY(Vert));    // Find largest y value in model
		maxVertex.z = max(maxVertex.z, XMVectorGetZ(Vert));    // Find largest z value in model
	}

	//Store Bounding Box's min and max vertices
	boundingBoxMin = XMVectorSet(minVertex.x -0.5f, minVertex.y - 0.5f, minVertex.z -0.5f, 0.0f);
	boundingBoxMax = XMVectorSet(maxVertex.x + 0.5f, maxVertex.y + 0.5f, maxVertex.z + 0.5f, 0.0f);
}

bool ModelClass::BoundingBoxCollision(XMVECTOR& firstObjBoundingBoxMinVertex,
	XMVECTOR& firstObjBoundingBoxMaxVertex,
	XMMATRIX& firstObjWorldSpace,
	XMVECTOR& secondObjBoundingBoxMinVertex,
	XMVECTOR& secondObjBoundingBoxMaxVertex,
	XMMATRIX& secondObjWorldSpace)
{
	//Is obj1's max X greater than obj2's min X? If not, obj1 is to the LEFT of obj2
	if (XMVectorGetX(firstObjBoundingBoxMaxVertex) > XMVectorGetX(secondObjBoundingBoxMinVertex))

		//Is obj1's min X less than obj2's max X? If not, obj1 is to the RIGHT of obj2
		if (XMVectorGetX(firstObjBoundingBoxMinVertex) < XMVectorGetX(secondObjBoundingBoxMaxVertex))

			//Is obj1's max Y greater than obj2's min Y? If not, obj1 is UNDER obj2
			if (XMVectorGetY(firstObjBoundingBoxMaxVertex) > XMVectorGetY(secondObjBoundingBoxMinVertex))

				//Is obj1's min Y less than obj2's max Y? If not, obj1 is ABOVE obj2
				if (XMVectorGetY(firstObjBoundingBoxMinVertex) < XMVectorGetY(secondObjBoundingBoxMaxVertex))

					//Is obj1's max Z greater than obj2's min Z? If not, obj1 is IN FRONT OF obj2
					if (XMVectorGetZ(firstObjBoundingBoxMaxVertex) > XMVectorGetZ(secondObjBoundingBoxMinVertex))

						//Is obj1's min Z less than obj2's max Z? If not, obj1 is BEHIND obj2
						if (XMVectorGetZ(firstObjBoundingBoxMinVertex) < XMVectorGetZ(secondObjBoundingBoxMaxVertex))

							//If we've made it this far, then the two bounding boxes are colliding
							return true;

	//If the two bounding boxes are not colliding, then return false
	return false;
}

void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}

void ModelClass::ShutdownBuffers()
{
	//// Release the index buffer.
	//if(m_indexBuffer)
	//{
	//	m_indexBuffer->Release();
	//	m_indexBuffer = 0;
	//}

	// Release the instance buffer.
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];


	// Set the buffer strides.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(InstanceType);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

 //   // Set the index buffer to active in the input assembler so it can be rendered.
	//deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}