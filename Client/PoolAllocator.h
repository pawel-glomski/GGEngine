#pragma once
#include <stdint.h>
#include "stdInclude.h"
#include "StackAllocator.h"

class Pool
{
public:
	explicit Pool(size_t size, size_t typeSize, uint8_t alignment);

	Pool() = default;

	Pool(const Pool & lref) = delete;

	Pool& operator=(const Pool & right) = delete;

	Pool(Pool&& rref);

	Pool& operator=(Pool && right);

	~Pool();

	void init(size_t size, size_t typeSize, uint8_t alignment);

	// deletes all allocated memory
	void reset();


	// Returned object may contain data from previous uses. 
	// Use placement new to initialize a new object on given memory (if needed) and if you do, remember to call destructor if object is not needed anymore and then free it as raw
	// or just free it with Pool::freeObject and then destructor will be called there
	void* allocRaw();

	// returned object is initizalized with given arguments; 
	// should be destroyed with Pool::freeWithDestructor, or call object's destructor by yourself and then free it as raw
	template<class T, class ... Args>
	T* allocObject(Args&&... args);

	// sets given memory as free, but does not call destructor;
	void freeRaw(void* object);

	// calls destructor and sets memory as free
	template<class T>
	void freeObject(T* object);

	// sets all memory as free
	void clear();


	size_t freeCount() const;

	size_t size() const;


	bool contains(void* ptr) const;

private:

	size_t		elemNum = 0;

	size_t		typeSize = 0;

	size_t		inUseCount = 0;

	uintptr_t	freeIndex = std::numeric_limits<uintptr_t>::max();

	uintptr_t	memory = 0;

	StackAllocator allocator;
};

template<class T, class ...Args>
inline T * Pool::allocObject(Args&&... args)
{
	ASSERT((sizeof(T) <= typeSize), "Tried to allocate object of a type, that size is greater from pool's set type size! Allocated nothing, returned nullptr");
	if (sizeof(T) <= typeSize)
	{
		void* allocatedObject = allocRaw();
		if (allocatedObject)
			return new(allocatedObject) T(std::forward<Args>(args)...);
	}
	return nullptr;
}

template<class T>
inline void Pool::freeObject(T * object)
{
	ASSERT((contains(object)), "Tried to free object that does not belong to pool");
	if (contains(object))
	{
		object->~T();
		freeRaw(object);
	}
}
