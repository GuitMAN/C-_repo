#pragma once
#include <vector>
#include "../Includes/ITerrainSceneNode.h"
#include "../Includes/VertexIndexData.h"
#include "../Includes/ISceneManager.h"


namespace Sam3d
{

class CTerrainSceneNode : public ITerrainSceneNode
{
public:

	//! constructor
	CTerrainSceneNode(ISceneNode* parent, ISceneManager* mgr, int id, 
		const Vector3f& position = Vector3f(0,0,0),
		const Vector3f& rotation = Vector3f(0,0,0),
		const Vector3f& scale = Vector3f(1.0f, 1.0f, 1.0f));

	~CTerrainSceneNode();

	virtual bool LoadTerrain(const char* FileName, TerrainOption mOption);
	virtual SMaterial& getMaterial(int i)
	{
		return Material;
	};
	
	virtual void OnPreRender();
	virtual void OnPostRender(int timeMs){};
	virtual void Render();

//	virtual bool getHeight(Vector2f pos, float& outHeight) = 0;

	void Initialize(int x,int y, IImage* pHeight);
protected:
	void generateIndices_STRIP();
	void generateIndices_LIST();
	// Возвращает индекс из карты высот 
    inline uInt _index( int x, int z ) const
    {
		return (x + z * Options.tileSize);
	};

	/** Возвращает  the  vertex coord for the given coordinates */
	inline float _vertex( int x, int z, int n )
	{
		return mPositionBuffer[x*3 + z*Options.tileSize*3 + n];
	};


	IVertexBuffer* pBufferHardware;
	float* mPositionBuffer;
	VertexData* MeshTerrain;//
	std::vector<uShort> Indices;
	SMaterial Material;
	int TerrainSize;
	TerrainOption Options;
	SRenderOp Op;	
};

};