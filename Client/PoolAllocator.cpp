#include "PoolAllocator.h"
#include <string>

Pool::Pool(size_t size, size_t typeSize, uint8_t alignment)
{
	init(size, typeSize, alignment);
}

void Pool::init(size_t numOfElements, size_t typeSize, uint8_t alignment)
{
	ASSERT(!memory, "PoolAllocator second initialisation is not possible before reset function");
	ASSERT(numOfElements, "Tried to initialise PoolAllocator with size == 0, init failed");
	ASSERT((typeSize >= alignment), "Size of pool's element type is smaller than alignment");
	ASSERT((numOfElements <= pow(2, 8 * typeSize) - 1), std::string("Type size is too small for this number of elements, this type size can handle only: ") 
		+ std::to_string((int)pow(2, 8 * typeSize) - 1) + " elements");

	if (!memory && numOfElements)
	{
		allocator.init(numOfElements*typeSize + alignment);
		elemNum = numOfElements;
		this->typeSize = typeSize;
		memory = (uintptr_t)allocator.allocRawAligned(numOfElements, alignment);
		clear();
	}
}

void Pool::clear()
{
	ASSERT(memory, "Tried to set as free all allocated memory before initialisation (there is nothing to set as free)");
	if (memory)
	{
		for (size_t i = 0; i < elemNum; i++)
			if(typeSize >= 4)
				*((uintptr_t*)(memory + (i * typeSize))) = (uintptr_t)(i + 1);	// last one is set out of range on purpose (it says that there is no free index)
			else if(typeSize == 2)
				*((uint16_t*)(memory + (i * typeSize))) = (uint16_t)(i + 1);
			else if(typeSize == 1)
				*((uint8_t*)(memory + (i * typeSize))) = (uint8_t)(i + 1);

		inUseCount = 0;
		freeIndex = 0;
	}
}

void* Pool::allocRaw()
{
	ASSERT(memory, "PoolAllocator use before its initialisation");
	ASSERT((freeIndex < elemNum), "No free memory to allocate");

	if (!memory || freeIndex >= elemNum)
		return nullptr;

	void* allocatedObject = (void*)(memory + freeIndex * typeSize);
	ptrdiff_t currIndex = freeIndex;
	freeIndex = *((uintptr_t*)(memory + freeIndex * typeSize));
	inUseCount++;

	return allocatedObject;
}


void Pool::freeRaw(void* object)
{
	ASSERT(memory, "PoolAllocator use before its initialisation");
	ASSERT(contains(object), "Tried to free object that does not belong to pool");

	if (contains(object))
	{
		uintptr_t newIndex = ((uintptr_t)object - memory) / typeSize;
		*((uintptr_t*)(memory + newIndex * typeSize)) = freeIndex < elemNum ? freeIndex : elemNum;
		freeIndex = newIndex;
		inUseCount--;
	}
}

size_t Pool::freeCount() const
{
	return elemNum - inUseCount;
}


size_t Pool::size() const
{
	return elemNum;
}

void Pool::reset()
{
	if (!memory) // pool already reseted
		return;

	allocator.reset();

	elemNum = 0;
	typeSize = 0;
	inUseCount = 0;
	freeIndex = std::numeric_limits<uintptr_t>::max();
	memory = 0;
}

bool Pool::contains(void * ptr) const
{
	return (memory && (uintptr_t)ptr >= memory && (uintptr_t)ptr < memory + elemNum * typeSize);
}


Pool::Pool(Pool && rref)
{
	*this = std::move(rref);
}

Pool & Pool::operator=(Pool && right)
{
	reset();
	elemNum = right.elemNum;
	typeSize = right.typeSize;
	inUseCount = right.inUseCount;
	freeIndex = right.freeIndex;
	memory = right.memory;
	allocator = std::move(right.allocator);

	right.allocator.reset();

	return *this;
}

Pool::~Pool()
{
	reset();
}