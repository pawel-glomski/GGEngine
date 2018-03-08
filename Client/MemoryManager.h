#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include "PoolAllocator.h"
#include "StackAllocator.h"

class MemoryManager
{
public:

	template<class T>
	struct PoolDeleter
	{
		void operator()(T* ptr)
		{
			std::cout << "custom pool deleter" << std::endl;
			MemoryManager::freeToPool<T>(ptr);
		}
	};

	template<class T>
	struct StackDeleter
	{
		void operator()(T* ptr)
		{
			std::cout << "custom stack deleter" << std::endl;
			if(MemoryManager::stack.contains(ptr))
				ptr->~T();
			// does not free memory, couse stack-allocated objects shouldn't be deleted in runtime, but only on shoutdown
			// so just call destructor and let MemoryManager::shoutDown function handle deallocation
		}
	};

public:
	static void startUp();
	static void shoutDown();

	// Pool allocator should be used only for temporary types (types that may be destroyed during the game) , that are used in large amount
	template<class T, class ...Args>
	static T* allocFromPool(Args&&... args);

	// T must be the same, or any base type that allocated object's type inherits from
	template<class T>
	static void freeToPool(T* ptr);

	static void clearPools();

private:
	MemoryManager() = delete;;

	template<class T>
	static void initNewPool(size_t quantity);

public:
	static StackAllocator stack;

private:
	static std::unordered_map<std::type_index, Pool> pools;
};

template<class T,  class ...Args>
inline T* MemoryManager::allocFromPool(Args&&... args)
{
	return (T*)( pools[std::type_index(typeid(T))].allocObject<T>( std::forward<Args>(args)... ) );
}

template<class T>
inline void MemoryManager::freeToPool(T * ptr)
{
	ASSERT(ptr, "Tried to free to pool object with nullptr address");
	if (ptr)
	{
		std::type_index typeIndex = std::type_index(typeid(*ptr));
		ASSERT(pools.count(typeIndex), "Tried to free object of a type, that pool doesn't exists");
		if (pools.count(typeIndex))
			pools[typeIndex].freeObject(ptr);
	}
}

template<class T>
inline void MemoryManager::initNewPool(size_t quantity)
{
	pools[std::type_index(typeid(T))].init(quantity, sizeof(T), alignof(T));
}
