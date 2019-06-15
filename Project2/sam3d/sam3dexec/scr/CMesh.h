#include "../Include/IMesh.h"

namespace Sam3d
{

	class CMesh: public IMesh
	{
	public:

		CMesh();
		~CMesh();

		virtual void addSubMesh(ISubMesh* buf);
		virtual ISubMesh* getSubMesh(uInt id);
		virtual SMaterial& getMaterialSubMesh(uInt id);
		virtual void deleteMesh();

		//! The meshbuffers of this mesh
		std::vector<ISubMesh*> pSubMesh;

	};
};