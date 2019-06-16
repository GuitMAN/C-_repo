#include "../Includes/IMesh.h"
#include <vector>

namespace Sam3d
{

	class CMesh: public IMesh
	{
	public:

		CMesh();
		~CMesh();

		virtual void addMeshBuffer(IMeshBuffer* buf);
		virtual IMeshBuffer* getMeshBuffer(uInt id);
//		virtual SMaterial& getMaterialSubMesh(uInt id);
		virtual void deleteMesh();

		//! The meshbuffers of this mesh
		std::vector<IMeshBuffer*> pMeshBuffer;

	};
};