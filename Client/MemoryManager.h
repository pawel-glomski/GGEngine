#pragma once
#include "PoolAllocator.h"
#include "StackAllocator.h"
#include "Character.h"
#include "VisualEffect.h"
#include "AudioEffect.h"
#include "CollisionShape.h"
#include "Projectile.h"

class MemoryManager
{
private:
	template<class T, class Allocator = std::allocator<T>>
	class PoolAllocator : public Pool<T, Allocator>
	{
	public:
		static PoolAllocator & instance();
	private:
		PoolAllocator() = default;;
	};

public:
	static MemoryManager & instance();

	void startUp();
	void shoutDown();

	template<class T>
	T* allocFromPool();

	template<class T>
	void freeToPool(T* ptr);

public:
	StackAllocator stack;

private:
	MemoryManager() = default;;
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

template<class T, class Allocator>
inline MemoryManager::PoolAllocator<T, Allocator>& MemoryManager::PoolAllocator<T, Allocator>::instance()
{
	static MemoryManager::PoolAllocator<T, Allocator> inst;
	return inst;
}
