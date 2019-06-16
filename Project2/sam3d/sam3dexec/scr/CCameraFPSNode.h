#pragma once

#include "../Includes/ICameraSceneNode.h"
#include "../Includes/ICursor.h"
#include "../Includes/Input.h"
//#include <vector>

namespace Sam3d
{

enum DEF_CAMERA
{
	_CAMERA_FORWARD, 
	_CAMERA_BACK, 
	_CAMERA_LEFT, 
	_CAMERA_RIGHT
};

//! Struct storing which key belongs to which action.
struct SKeyMap
{
	DEF_CAMERA Action;
//	OIS::KEY_CODES KeyCode;
};



class CCameraFPSNode: public ICameraSceneNode
{
public:
	CCameraFPSNode(ISceneNode* parent, ISceneManager* mgr, int id);
	virtual ~CCameraFPSNode(void);

	virtual void OnPreRender();
	virtual void OnPostRender(uInt timeMs);
	virtual void Render();
	virtual void moveRelative(const Vector3f& vec);
//	virtual bool OnInput(CInput* input); 
	virtual void recalculateProjectionMatrix();
protected:	
	
//	void Move(DEF_CAMERA dir);


//	Matrix4f Proj; //Проекционная матрица
//	Matrix4f View; //Видовая матрица камеры

	Vector3f Target;
	Vector3f UpVector;


	float fovy;		// Field of view, in radians. 
	float aspect;	// Aspect ratio. 
	float zn;		// value of the near view-plane. 
	float zf;		// Z-value of the far view-plane.

	uInt LastAnimationTime;
	// Скорость, которая прибавится в текущей обработке
	Vector3f DeltaSpeed;
	ICursor *Cursor;
	struct SCamKeyMap
	{
		SCamKeyMap() {};
//		SCamKeyMap(int a, OIS::KEY_CODES k) : action(a), keycode(k) {}

		int action;
//		OIS::KEY_CODES keycode;
	};
	bool CursorKeys[4];
	std::vector<SCamKeyMap> KeyMap;
};

};
