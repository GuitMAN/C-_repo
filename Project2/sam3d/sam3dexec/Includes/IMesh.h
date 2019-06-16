#pragma once
#include "IMeshBuffer.h"



namespace Sam3d
{

	class IMesh : IBase
	{
	public:

		virtual void addSubMesh(IMeshBuffer* buf);
		virtual IMeshBuffer* getSubMesh(uInt id);
		virtual SMaterial& getMaterialSubMesh(uInt id);
		virtual void deleteMesh();

	};
};