#pragma once

#include "IBase.h"
#include <string>
#include <list>
#include "../scr/core/Matrix4f.h"
#include "../scr/core/Quaternionf.h"
#include "../scr/core/SMaterial.h"
#include "../scr/core/Vector3f.h"

namespace Sam3d
{

class ISceneManager;
class ISceneNode: public IBase
{
public:
    
	ISceneNode(ISceneNode* parent, ISceneManager* mgr, int id=-1,
		const Vector3f& position = Vector3f(0,0,0),
		const Vector3f& rotation = Vector3f(0,0,0),
		const Vector3f& scale = Vector3f(1.0f, 1.0f, 1.0f))
		:Parent(parent), SceneManager(mgr),Translation(position),
		Rotation(rotation), Scale(scale)
	{
		if (Parent)
			Parent->addChild(this);
		IsVisible = true;
		UpdateAbsolutePosition();	
	};
	
	//! Destructor
	virtual ~ISceneNode()
	{
		// delete all children
		std::list<ISceneNode*>::iterator it = Children.begin();
		for (; it != Children.end(); ++it)
			(*it)->Release();

	};

	virtual void OnPreRender()
	{
			if (IsVisible)
			{
				std::list<ISceneNode*>::iterator it = Children.begin();
				for (; it != Children.end(); ++it)
					(*it)->OnPreRender();
			}


	};
	virtual void OnPostRender(uInt timeMs)
	{
			if (IsVisible)
			{
				std::list<ISceneNode*>::iterator it = Children.begin();
				for (; it != Children.end(); ++it)
					(*it)->OnPostRender(timeMs);
			}

	};
	//! Renders the node.
	virtual void Render() = 0;

	//! Returns the name of the node.
	//! \return Returns name as wide character string.
	virtual const std::string getName() const
	{
		return Name;
	}


	//! Sets the name of the node.
	//! \param name: New name of the scene node.
	virtual void setName(const std::string name)
	{
		Name = name;
	}

	virtual bool isVisible()
	{
		return IsVisible;
	}


	//! Sets if the node should be visible or not. All children of this node won't be visible too.
	virtual void setVisible(bool isVisible)
	{
		IsVisible = isVisible;
	}

	//! Returns the id of the scene node. This id can be used to identify the node.
	virtual int getID()
	{
		return ID;
	}

	//! sets the id of the scene node. This id can be used to identify the node.
	virtual void setID(int id)
	{
		ID = id;
	}


	//! Adds a child to this scene node. If the scene node already
	//! has got a parent, it is removed from there as child.
	virtual void addChild(ISceneNode* child)
	{
		if (child)
		{
			child->remove(); // remove from old parent				
			Children.push_back(child);
			child->Parent = this;				
		}
	}

	//! Removes a child from this scene node.
	//! \return Returns true if the child could be removed, and false if not.
	virtual bool removeChild(ISceneNode* child)
	{
		std::list<ISceneNode*>::iterator it = Children.begin();
		for (; it != Children.end(); ++it)
		if ((*it) == child)
		{
			(*it)->Release();
			Children.erase(it);
			return true;
		}

		return false;
	}


	//! Removes all children of this scene node
	virtual void removeAll()
	{
		std::list<ISceneNode*>::iterator it = Children.begin();
		for (; it != Children.end(); ++it)
			(*it)->Release();

		Children.clear();
	}

	//! Removes this scene node from the scene, deleting it.
	virtual void remove()
	{
		if (Parent)
			Parent->removeChild(this);
	}


	//! Returns a const reference to the list of all children.
	const std::list<ISceneNode*>& getChildren() const
	{
		return Children;
	}


	//! Changes the parent of the scene node.
	virtual void setParent(ISceneNode* newParent)
	{
		remove();

		Parent = newParent;

		if (Parent)
			Parent->addChild(this);

		Release();
	}

	virtual ISceneNode* getParent()
	{
		return Parent;
	};

	virtual ISceneManager* getSceneManager()
	{
		return SceneManager;
	};
	virtual Matrix4f getTransformation()
	{
		Matrix4f mat;
		mat.setRotationDeg(Rotation);
		mat.setTranslation(Translation);
/*
		if (Scale != Vector3f(1,1,1))
		{
			Matrix4f smat;
			smat.setScale(Scale);
			mat *= smat;
		}
*/
		return mat;
	};

	virtual SMaterial& getMaterial(int i)
	{
		return *((SMaterial*)0);
	}
	
	void setMaterialTexture(int textureLayer, ITexture* texture)
	{
		if (textureLayer<0)
			return;

	//	for (int i=0; i<getMaterialCount(); ++i)
					getMaterial(0).Texture[textureLayer] = texture;
	};



	virtual void setRotation(Vector3f& newrot)
	{
		Rotation = newrot;
		Rotate.FromEuler(Rotation);
	};
	
	virtual Quaternionf getRotateQuant()
	{
		return Rotate;

	};

	virtual Vector3f getRotation()
	{
		return Rotation;
	};

	virtual void setScale(Vector3f& newscale)
	{
		Scale = newscale;
	};
	
	virtual Vector3f getScale()
	{
		return Scale;
	};

	virtual void setPosition(Vector3f& newpos)
	{
		Translation = newpos;
	};
	virtual Vector3f getPosition()
	{
		return Translation;
	}
	//! updates the absolute position based on the relative and the parents position
	virtual void UpdateAbsolutePosition()
	{
		if (Parent)
			AbsoluteTransformation = Parent->getTransformation() * getTransformation();
		else
			AbsoluteTransformation = getTransformation();
	}


protected:
	
	//! name of the scene node.
	std::string Name;
	//! id of the node.
    int ID;
	//вращение
	Quaternionf Rotate; 
	//! Матрица трансцормации объекта
	Matrix4f AbsoluteTransformation;
	//! Вектор трансляции относительно сцены
	Vector3f Translation;
	//! Поворот относительно сцены
	Vector3f Rotation;
	//! Мысшабирование объекта
	Vector3f Scale;


	//! Уакзатель на родительский объект
	ISceneNode* Parent;
	//! Список дочерних объектов сцены
	std::list<ISceneNode*> Children;

	//! Указатель на менеджер сцены
	ISceneManager* SceneManager;
	//! видимый объект
	bool IsVisible;


};

};