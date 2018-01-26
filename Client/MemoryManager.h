#pragma once
#include "Singleton.h"
#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "Character.h"
#include "VisualEffect.h"
#include "AudioEffect.h"
#include "CollisionShape.h"
#include "Projectile.h"

class MemoryManager : public Singleton<MemoryManager>
{
	template<class T, class Allocator = std::allocator<T>>
	class PoolAllocator : public Singleton<Pool<T, Allocator>>{};

public:
	void startUp();
	void shoutDown();

	template<class T>
	T* allocFromPool();

	template<class T>
	void freeToPool(T* ptr);

public:
	StackAllocator stack;
};

template<class T>
inline T * MemoryManager::allocFromPool()
{
	return PoolAllocator<T>::instance().alloc();
}

template<class T>
inline void MemoryManager::freeToPool(T * ptr)
{
	PoolAllocator<T>::instance().free(ptr);
}