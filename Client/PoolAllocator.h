#pragma once
#include "stdInclude.h"
#include <vector>


template<class T, class Allocator = std::allocator<T>>
class Pool
{
public:
	explicit Pool(size_t size);
	Pool() = default;
	Pool(const Pool & lref) = delete;
	Pool(Pool&& rref) = delete;
	Pool<T>& operator=(const Pool & right) = delete;
	Pool<T>& operator=(Pool && right) = delete;

	~Pool();

	void init(size_t size);
	void reset();

	// returns ptr to free to use object (object may contain data from previous uses)
	T* alloc();

	// sets given object as free, but does not call destructor
	void free(T* object);
	// sets given object as free, but does not call destructor
	void free(size_t index);
	// sets all objects as free
	void clear();

	T* getArray();
	const T* getArray() const;

	size_t freeCount() const;
	size_t size() const;

	bool isValid(T* ptr) const;

private:
	Allocator	allocator;
	size_t		poolSize =	 0;
	size_t		inUseCount = 0;
	ptrdiff_t	freeIndex =	 -1;
	T*			objects =	 nullptr;
	void**		freeList =	 nullptr;
};

template<class T, class Allocator>
inline Pool<T, Allocator>::Pool(size_t size)
{
	init(size);
}

template<class T, class Allocator>
inline void Pool<T, Allocator>::init(size_t size)
{
	ASSERT(!objects, "PoolAllocator second initialisation is not possible before reset function");
	ASSERT(size, "Tried to initialise PoolAllocator with size == 0, init failed");
	if (!objects && size)
	{
		poolSize = size;
		objects = allocator.allocate(size);
		for (size_t i = 0; i < size; i++)
			allocator.construct(&objects[i]);
		freeList = new void*[size];
		clear();
	}
}

template<class T, class Allocator>
inline void Pool<T, Allocator>::clear()
{
	ASSERT(freeList, "Tried to set as free all allocated objects before initialisation (there is nothing to set as free)");
	if (freeList)
	{
		for (size_t i = 0; i < poolSize - 1; i++)
			freeList[i] = (&freeList[i + 1]);
		freeList[poolSize - 1] = nullptr;
		inUseCount = 0;
		freeIndex = 0;
	}
}

template<class T, class Allocator>
inline T * Pool<T, Allocator>::alloc()
{
	ASSERT(objects, "PoolAllocator use before its initialisation");
	ASSERT((freeIndex >= 0), "Tried to allocate from pool with no free memory");

	if (!objects || freeIndex < 0)
		return nullptr;

	T* allocObject = &objects[freeIndex];
	ptrdiff_t currIndex = freeIndex;
	freeIndex = (ptrdiff_t)((uintptr_t*)freeList[freeIndex] - (uintptr_t*)freeList);
	freeList[currIndex] = nullptr;
	inUseCount++;
	
	return allocObject;
}

template<class T, class Allocator>
inline void Pool<T, Allocator>::free(size_t index)
{
	ASSERT((index < poolSize), "Tried to free object that does not belong to pool");
	if (objects && index < poolSize)
		free(&objects[index]);
}

template<class T, class Allocator>
inline void Pool<T, Allocator>::free(T * object)
{
	ASSERT(objects, "PoolAllocator use before its initialisation");
	ASSERT(((object >= objects) && (object < &objects[poolSize])), "Tried to free object that does not belong to pool");

	if (objects && (object >= objects) && (object < &objects[poolSize]))
	{
		ptrdiff_t newIndex = object - objects;
		freeList[newIndex] = freeIndex >= 0 ? &freeList[freeIndex] : nullptr;
		freeIndex = newIndex;
		inUseCount--;
	}
}

template<class T, class Allocator>
inline T * Pool<T, Allocator>::getArray()
{
	ASSERT(objects, "Tried to get array before pool initialisation, returned nullptr");
	return objects;
}

template<class T, class Allocator>
inline const T * Pool<T, Allocator>::getArray() const
{
	ASSERT(objects, "Tried to get array before pool initialisation, returned nullptr");
	return objects;
}

template<class T, class Allocator>
inline size_t Pool<T, Allocator>::freeCount() const
{
	return poolSize - inUseCount;
}

template<class T, class Allocator>
inline size_t Pool<T, Allocator>::size() const
{
	return poolSize;
}

template<class T, class Allocator>
inline bool Pool<T, Allocator>::isValid(T * ptr) const
{
	ptrdiff_t index = (ptrdiff_t)(ptr - objects);
	// object is valid (not free) when address in "freeList" with the same index as object's index in "objects" array is set to nullptr and its not the last free object in a pool
	return (freeList[index] == nullptr && freeIndex != index);
}

template<class T, class Allocator>
inline void Pool<T, Allocator>::reset()
{
	if (!objects) // pool already reseted
		return;
	delete[] freeList;
	for (size_t i = 0; i < poolSize; i++)
		allocator.destroy(&objects[i]);
	allocator.deallocate(objects, poolSize);

	poolSize = 0;
	inUseCount = 0;
	freeIndex = -1;
	objects = nullptr;
	freeList = nullptr;
}

template<class T, class Allocator>
inline Pool<T, Allocator>::~Pool()
{
	reset();
}