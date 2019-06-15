#pragma once

#include "../Includes/ISceneNode.h"
#include "../Includes/ISceneManager.h"
#include "../Includes/ITexture.h"
#include "../scr/core/S3DVertex.h"

namespace Sam3d
{

class CSkyBox: public ISceneNode
{
public:	
	CSkyBox(ITexture *top,ITexture *bottom,ITexture *left, ITexture *right,
		ITexture *front,ITexture *back, ISceneNode* parent, ISceneManager* mgr, int id);
	~CSkyBox(void);

	virtual void OnPreRender();
	virtual void OnPostRender(int timeMs){};
	virtual void Render();
	
protected:

	uShort Indices[4];
	SRenderOp Op;
	SMaterial Mat[6];
	
};

};