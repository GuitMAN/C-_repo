#pragma once
#include "../Includes/includes.h"

using namespace Sam3d;

	class ExampleApp
	{
	public:
		ExampleApp();
		~ExampleApp();

		bool setup();

		void Run();

		void shutdown();
		//	void processInput();


		IWindow* createWindow();

		IWindow* Window;

	protected:
		//	ICameraSceneNode* Camera;
		//	IRender* Render;
		//	ISceneManager* SceneManager;
		ICursor* Mouse;
		//	CInput* Keyboard;
		Vector3f TranslateVector;
		Vector3f RotCamera;
		float mMoveScale;
		float mRotSpeed;
		float mSpeedLimit;
		bool isQuite;
	};
