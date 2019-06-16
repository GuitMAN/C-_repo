#pragma once


namespace Sam3d
{

	class IMesh 
	{
	public:

		virtual void addSubMesh(ISubMesh* buf);
		virtual ISubMesh* getSubMesh(uInt id);
		virtual SMaterial& getMaterialSubMesh(uInt id);
		virtual void deleteMesh();

	};
};