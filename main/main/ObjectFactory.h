#pragma once
#include "include.h"

class ObjectFactory
{
public:

	void Release();

public:
	ImageStorager* CreateImageStorager();
	ObjectFactory* CreateObjectFactory();

private:
	ObjectFactory();
	~ObjectFactory();
	static ObjectFactory* instance;
};

