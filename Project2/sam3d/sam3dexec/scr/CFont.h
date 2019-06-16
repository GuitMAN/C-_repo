#pragma once
#include "../Includes/IFont.h"
#include "../Includes/IRender.h"
#include "../Includes/ISceneNode.h"
#include "../Includes/ISceneManager.h"


namespace Sam3d
{

	class CFont : public IFont
	{
	public:
		CFont(ISceneNode* parent, ISceneManager* mgr, int id, IRender* driver)
			//			:CFont(parent, mgr, id), Driver(driver), Texture(0)
		{};
		virtual ~CFont() {};
		virtual bool Load(char* name);
		virtual void Draw(char* name, SColor color, Position2d<int>& position);
		virtual void Render() {};

	private:
		//		bool loadTexture(ITexture* texture);
		RECT offset[256];
		IRender* Driver;
		//		ITexture* Texture;
	};

};