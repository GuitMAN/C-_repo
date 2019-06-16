#include "CMesh.h"

namespace Sam3d
{

	CMesh::CMesh()
	{

	};
	CMesh::~CMesh()
	{
	};

	void CMesh::addMeshBuffer(IMeshBuffer* buf)
	{
		if (buf)
		{
			pMeshBuffer.push_back(buf);
		};
	};
	
	IMeshBuffer* CMesh::getMeshBuffer(Sam3d::uInt id)
	{
		return pMeshBuffer[id];
	};

//	SMaterial& CMesh::getMaterialSubMesh(uInt id)
//	{
//		return pSubMesh[id]->getMaterial();
//	};

	//Delete vector of pMeshBuffer
	void CMesh::deleteMesh()
	{
		while (!pMeshBuffer.empty())
		{
			pMeshBuffer.pop_back();
		}
	};

};