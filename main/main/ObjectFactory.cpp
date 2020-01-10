#include "ObjectFactory.h"



ObjectFactory::ObjectFactory()
{

}

ObjectFactory::~ObjectFactory()
{

}

ObjectFactory* ObjectFactory::CreateObjectFactory() 
{
	if (ObjectFactory::instance != NULL) {
		return ObjectFactory::instance;
	}

	ObjectFactory::instance = new ObjectFactory;
}

ImageStorager* ObjectFactory::CreateImageStorager() 
{
	if (ImageStorager::instance != NULL) {
		return ImageStorager::instance;
	}

	ImageStorager::instance = new ImageStorager;
}