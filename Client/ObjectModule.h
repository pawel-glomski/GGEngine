#pragma once
#include "Module.h"
#include "EntityBase.h"
#include "SystemsHolder.h"

#include "MotionSystem.h"
#include "DisplaySystem.h"

class ObjectModule : public Module<DisplayModule>
{

	template<class T>
	using StdUPtr_t = std::unique_ptr<T>;

	using ObjPtr_t = StdUPtr_t<EntityBase>;

	using ObjKey_t = CPtr_t<IdentityComponent>;

	using ObjContainer_t = std::unordered_map<ObjKey_t, ObjPtr_t>;


	using DestroyedObjects_t = std::vector<ObjKey_t>;


public:

	template<class ...MTypes>
	ObjectModule(const MDepPack_t<MTypes...> & dependencies) : ModuleBase_t(dependencies)
	{}


	virtual void shutdown() override;

	virtual void update(float_t dt) override;


	template<class T>
	T& spawnObject(IdScope scope, Lifetime lifetime);

	void destroyTempObject(const ObjKey_t & objectKey);


private:

	void destroyAnyObject(const ObjKey_t & objectKey);

	void removeDestroyedObjects();


private:

	ObjContainer_t objects;

	DestroyedObjects_t destroyedObjects;

	SystemsHolder<MotionSystem, DisplaySystem> systemsHolder;

};




template<class T>
inline T & ObjectModule::spawnObject(IdScope scope, Lifetime lifetime)
{
	StdUPtr_t<T> object = std::make_unique<T>();
	T& objectRef = *object;
	ObjKey_t objectKey = objectRef.getComponentPtr<IdentityComponent>();

	objectKey->createIdentity(scope, lifetime);
	objectRef.construct(*static_cast<ObjectModule*>(this));

	systemsHolder.addObject(objectRef);
	objects.emplace(std::make_pair(std::move(objectKey), std::move(object)));

	return objectRef;
}