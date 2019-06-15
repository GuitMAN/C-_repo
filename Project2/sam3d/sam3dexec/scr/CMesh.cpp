#include "CMesh.h"

namespace Sam3d
{

	CMesh::CMesh()
	{

	};
	CMesh::~CMesh()
	{
	};

	void CMesh::addSubMesh(ISubMesh* buf)
	{
		if (buf)
		{
			pSubMesh.push_back(buf);
		};
	};
	
	ISubMesh* CMesh::getSubMesh(Sam3d::uInt id)
	{
		return pSubMesh[id];
	};

	SMaterial& CMesh::getMaterialSubMesh(uInt id)
	{
		return pSubMesh[id]->getMaterial();
	};

	void CMesh::deleteMesh()
	{
	};

};