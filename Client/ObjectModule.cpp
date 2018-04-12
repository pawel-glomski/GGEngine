#include "ObjectModule.h"

void ObjectModule::destroyTempObject(const ObjKey_t & objectKey)
{
	ASSERT((objectKey->getLifetime() == Lifetime::Temp), "Cannot destroy non-temp object");
	if (objectKey->getLifetime() == Lifetime::Temp)
		destroyAnyObject(objectKey);
}


void ObjectModule::destroyAnyObject(const ObjKey_t & objectKey)
{
	ASSERT(objects.count(objectKey), "No object at given key to destroy");
	if (objects.count(objectKey))
	{
		destroyedObjects.push_back(objectKey);
		for (auto& attached : objectKey->getAttached())
			destroyAnyObject(attached);
	}
}


void ObjectModule::update(float_t dt)
{
	for (auto & object : objects)
		object.second->uniqueUpdate(dt);

	systemsHolder.addPendingObjects();

	systemsHolder.update(dt, dependencies, *static_cast<ObjectModule*>(this));

	removeDestroyedObjects();
}


void ObjectModule::removeDestroyedObjects()
{
	for (auto& objectKey : destroyedObjects)
	{
		ASSERT(objects.count(objectKey), "No object to destroy at the given key");

		systemsHolder.removeObject(objectKey);

		ObjPtr_t object = std::move(objects[objectKey]);
		objects.erase(objectKey);
		objectKey.reset();
		object.reset();
	}
	destroyedObjects.clear();
}


void ObjectModule::shutdown()
{
	ModuleBase_t::shutdown();

	for (auto & objectNode : objects)
		if (!objectNode.first->isAttached())
			destroyAnyObject(objectNode.first);
	removeDestroyedObjects();
	objects.clear();
}