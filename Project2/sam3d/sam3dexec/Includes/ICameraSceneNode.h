#pragma once
#include "ISceneNode.h"



namespace Sam3d
{

	class ICameraSceneNode: public ISceneNode
	{
	public:
		//! Constructor
		ICameraSceneNode(ISceneNode* parent, ISceneManager* mgr, int id, 
				const Vector3f& position = Vector3f(0,0,0),
				const Vector3f& rotation = Vector3f(0,0,0),
				const Vector3f& scale = Vector3f(1.0f,1.0f,1.0f))
				: ISceneNode(parent, mgr, id, position, rotation, scale) {}
	
		virtual ~ICameraSceneNode(){};
		virtual void moveRelative(const Vector3f& vec)=0;
		virtual void recalculateProjectionMatrix()=0;
	};

};