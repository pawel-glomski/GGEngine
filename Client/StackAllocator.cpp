#include "stdInclude.h"
#include "StackAllocator.h"

StackAllocator::StackAllocator(size_t sizeInBytes)
{
	init(sizeInBytes);
}

void StackAllocator::init(size_t sizeInBytes)
{
	ASSERT(!bottomMarker, "Tried to initialise already initialised StackAllocator, \"reset\" member function must be called first!");
	ASSERT(sizeInBytes, "Tried to initialise StackAllocator with size 0");
	if (sizeInBytes && !bottomMarker)
	{
		this->sizeInBytes = sizeInBytes;
		bottomMarker = (Marker)(operator new(sizeInBytes));
		topMarker = bottomMarker;
	}
}

void * StackAllocator::allocUnaligned(size_t sizeInBytes)
{
	ASSERT(bottomMarker, "Stack allocator use before its initialisation");
	if (bottomMarker && topMarker + sizeInBytes - 1 < bottomMarker + this->sizeInBytes)
	{
		topMarker += sizeInBytes;
		return (void*)(topMarker - sizeInBytes);
	}
	ASSERT(false, "Not enough memory to allocate more!");
	return nullptr;
}

void * StackAllocator::allocAligned(size_t sizeInBytes, uint8_t alignment)
{
	ASSERT((alignment & (alignment - 1)) == 0, "Alignment is not power of 2");

	uintptr_t rawAddress = (uintptr_t)allocUnaligned(sizeInBytes + alignment);
	if (!rawAddress)
		return nullptr;
	uintptr_t mask = (alignment - 1);
	uint8_t misalignment = (rawAddress & mask);
	ptrdiff_t adjustment = alignment - misalignment;
	uintptr_t alignedAddress = rawAddress + adjustment;

	uint8_t* pAdjustment = (uint8_t*)(alignedAddress - 1);
	*pAdjustment = adjustment;

	return (void*)alignedAddress;
}

StackAllocator::Marker StackAllocator::getMarker() const
{
	ASSERT(topMarker, "Returned nullptr as Stack's topMarker");
	return topMarker;
}

void StackAllocator::clear()
{
	ASSERT(bottomMarker, "Tried to free stack to bottom when there is no memory allocated by stack");
	topMarker = bottomMarker;
}

void StackAllocator::reset()
{
	ASSERT(bottomMarker, "Empty StackAllocator destruction/reset. Ok if its shown on game's end (probably reset was called on shoutdown)");
	if (bottomMarker)
		operator delete ((void*)(bottomMarker), sizeInBytes);

	bottomMarker = 0;
	topMarker = 0;
	sizeInBytes = 0;
}

StackAllocator::~StackAllocator()
{
	reset();
}