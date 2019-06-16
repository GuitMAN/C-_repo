#pragma once
#include "IMeshBuffer.h"



namespace Sam3d
{

	class IMesh : IBase
	{
	public:

		virtual void addMeshBuffer(IMeshBuffer* buf);
		virtual IMeshBuffer* getMeshBuffer(uInt id);
//		virtual SMaterial& getMaterialSubMesh(uInt id);
		virtual void deleteMesh();

	};
};