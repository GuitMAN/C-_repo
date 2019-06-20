#pragma once
#include "types.h"


namespace Sam3d
{

// Базовый объект
class IBase
{
public:
	IBase()
	{
		AddRef();
	}

	~IBase() {
		if (ReferenceCounter)
		{
			Release();
		}
	};

	bool Release()
	{
		--ReferenceCounter;
		if (ReferenceCounter)
		{	
			delete this;
			return true;
		}
		return false;
	}
private:
	
	void AddRef()
	{
		++ReferenceCounter;
	};
	int	ReferenceCounter =0;
};

};