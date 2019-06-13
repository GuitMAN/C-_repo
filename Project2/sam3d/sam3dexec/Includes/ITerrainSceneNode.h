#pragma once

#include "ISceneNode.h"
#include "core/Vector3f.h"
	
namespace Sam3d
{

class TerrainOption
{
public:
	TerrainOption()
	{
		pageSize = 0;
		tileSize = 0;
		detailTile = 0;
		light = false;
		coloured = false;
	};
    // The size of one edge of a terrain page, in vertices
    uInt pageSize;
    // The size of one edge of a terrain tile, in vertices
    uInt tileSize; 
    // Precalculated number of tiles per page
    uInt tilesPerPage;
    // The number of times to repeat a detail texture over a tile
    uInt detailTile;
	// Whether dynamic lighting is enabled
	bool light;
	// Whether vertex colours are enabled
	bool coloured;
	// Pointer to the material to use to render the terrain
    // MaterialPtr terrainMaterial;
};

class ISceneManager;
class ITerrainSceneNode : public ISceneNode
{
public:
	//! constructor
	ITerrainSceneNode(ISceneNode* parent, ISceneManager* mgr, int id, 
		const Vector3f& position = Vector3f(0,0,0),
		const Vector3f& rotation = Vector3f(0,0,0),
		const Vector3f& scale = Vector3f(1.0f, 1.0f, 1.0f))
			: ISceneNode(parent, mgr, id, position, rotation, scale)
	{
	}
	virtual bool LoadTerrain(const char* FileName, TerrainOption mOption)=0;
//	virtual SMaterial* getMaterial()=0;  
//	virtual bool getHeight(Vector2f pos, float& outHeight) = 0;
//	virtual void setDebugLOD(s32 i) = 0;

};


};