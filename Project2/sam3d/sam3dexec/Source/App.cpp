class ExampleApp
{
public:
	ExampleApp()
	{
		Window = 0;
		Camera = 0;
		Render = 0;
		SceneManager = 0;
		Mouse = 0;
		Keyboard = 0;
		mMoveScale = 0.8f;
		mRotSpeed = 0.5f;
		isQuite = true;
	};
	~ExampleApp() {};

	bool setup()
	{
		if (!createWindow())return false;
		Render = Window->getRender();
		SceneManager = Window->getSceneManager();
		Keyboard = Window->getInput();
		Mouse = Window->getCursor();
		createCamera();
		createScene();

		return true;

	};


	ICameraSceneNode* createCamera()
	{
		Camera = SceneManager->addCamera();
		Camera->setScale(Vector3f(1, 1, 1));
		RotCamera.Set(0, 0, 0);
		TranslateVector.Set(200, 100, 200);
		Camera->setPosition(Vector3f(-120, 123, -145));
		Mouse->setPosition(300, 300);
		return Camera;
	};
	void createScene()
	{
		//Создание Скайбокса
		SceneManager->addSkyBoxNode(Render->LoadTextureFromFile("SkyBox/SkyMATTER/pos_up.tga"),
			Render->LoadTextureFromFile("SkyBox/SkyMATTER/neg_dn.tga"),
			Render->LoadTextureFromFile("SkyBox/SkyMATTER/neg_lf.tga"),
			Render->LoadTextureFromFile("SkyBox/SkyMATTER/pos_rt.tga"),
			Render->LoadTextureFromFile("SkyBox/SkyMATTER/neg_fr.tga"),
			Render->LoadTextureFromFile("SkyBox/SkyMATTER/pos_bk.tga"));

		//Сщздание ландшафта
		TerrainOption opt;
		opt.pageSize = 512;
		opt.detailTile = 32;
		opt.tileSize = 512;
		opt.tilesPerPage = 32;
		Sam3d::ITerrainSceneNode* tr = SceneManager->addTerrainNode("terrain/terrain.tga", opt,
			Vector3f(0, 0, 0),			//position
			Vector3f(0, 0, 0),			//rotate
			Vector3f(10.f, 0.5f, 10.f));	//scale 

		tr->setMaterialTexture(0, Render->LoadTextureFromFile("terrain/terrain_texture.tga"));
		tr->setMaterialTexture(1, Render->LoadTextureFromFile("terrain/grass.tga"));
		SMaterial& mt = tr->getMaterial(0);
		mt.MaterialType = Sam3d::EMT_DETAL_MAP;
		mt.Wireframe = false;
		mt.BackfaceCulling = true;
		mt.FilterOptions = Sam3d::TFO_TRILINEAR;

	};

	void shutdown()
	{
		if (Window) Window->Release();
	};

	void Run()
	{
		int time = 0;
		while (isQuite && Window->Run())
		{
			processMouse();
			processInput();
			moveCamera();
			Render->BeginScene(true, true, Sam3d::SColor(100, 10, 10, 10));
			if (SceneManager) SceneManager->Render();
			Render->EndScene();

			int fps = Render->getFPS();
			if (time >= 300)
			{
				time = 0;
				Window->SetCaption(toStr("3D приложение: %i  ", fps));
			}
			else time++;

		};
	};

	void processInput()
	{
		//Проверка на выход
		if (Keyboard->keys.keyDown[OIS::KEY_ESCAPE]) isQuite = false;

		//двигаем камеру
		Vector3f movedir(0, 0, 1), strafe(1, 0, 0);
		// Находим вектор направления взгляда
		movedir.RotateX(Camera->getRotation().x);
		movedir.RotateY(-Camera->getRotation().y);
		// Находим верктор бокового движения
		strafe.RotateX(Camera->getRotation().x);
		strafe.RotateY(-Camera->getRotation().y);

		if (Keyboard->keys.keyDown[OIS::KEY_UP] | Keyboard->keys.keyDown[OIS::KEY_W])
			TranslateVector += movedir * (+mMoveScale);
		if (Keyboard->keys.keyDown[OIS::KEY_DOWN] | Keyboard->keys.keyDown[OIS::KEY_S])
			TranslateVector += movedir * (-mMoveScale);

		if (Keyboard->keys.keyDown[OIS::KEY_RIGHT] | Keyboard->keys.keyDown[OIS::KEY_D])
			TranslateVector += strafe * (+mMoveScale);
		if (Keyboard->keys.keyDown[OIS::KEY_LEFT] | Keyboard->keys.keyDown[OIS::KEY_A])
			TranslateVector += strafe * (-mMoveScale);
		//--------------------------------------------
	};

	void processMouse()
	{
		Dimension2d<int> winsize = Window->getWindowSize();
		Position2d<int> MouseCenter;
		MouseCenter.x = 300;//int (winsize.Width/2);
		MouseCenter.y = 300;//int (winsize.Height/2);
		Position2d<int> MousePos = Mouse->getPosition();
		Position2d<int> offCur;
		offCur.x = MousePos.x - MouseCenter.x;
		offCur.y = MousePos.y - MouseCenter.y;
		RotCamera.x += (float)offCur.y * mRotSpeed;
		RotCamera.y += (float)offCur.x * mRotSpeed;
		CUT_RANGE(0, RotCamera.y, 360);
		CUT_RANGE(0, RotCamera.x, 360);
		Mouse->setPosition(MouseCenter.x, MouseCenter.y);

	};

	void moveCamera()
	{
		Camera->setRotation(RotCamera);
		Camera->setPosition(TranslateVector);
	}

	IWindow* createWindow()
	{
		Window = Sam3d::createWindow("3D приложение", Dimension2d<int>(800, 600), 32, false, false);
		return Window;
	};

	IWindow* Window;
protected:
	ICameraSceneNode* Camera;
	IRender* Render;
	ISceneManager* SceneManager;
	ICursor* Mouse;
	CInput* Keyboard;
	Vector3f TranslateVector;
	Vector3f RotCamera;
	float mMoveScale;
	float mRotSpeed;
	float mSpeedLimit;
	bool isQuite;
};