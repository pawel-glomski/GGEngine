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
		bottomMarker = reinterpret_cast<Marker>(::operator new(sizeInBytes));
		topMarker = bottomMarker;
	}
}

void * StackAllocator::allocRawUnaligned(size_t sizeInBytes)
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

void * StackAllocator::allocRawAligned(size_t sizeInBytes, uint8_t alignment)
{
	ASSERT((alignment & (alignment - 1)) == 0, "Alignment is not power of 2");

	uintptr_t rawAddress = (uintptr_t)allocRawUnaligned(sizeInBytes + alignment);
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

void StackAllocator::freeToRawUnaligned(void * marker)
{
	ASSERT(marker, "Tried to free memory to a nullptr");
	ASSERT(contains(marker), "Tried to free memory that stack does not contain");
	if (marker && contains(marker))
	{
		uintptr_t mark = (uintptr_t)marker;
		ASSERT((mark < topMarker), "Tried to free memory to a marker that lies further than current stack's top marker");

		if (mark < topMarker)
			topMarker = mark;
	}
}

void StackAllocator::freeToRawAligned(void * marker)
{
	ASSERT(marker, "Tried to free memory to a nullptr");
	if (marker)
	{
		uintptr_t mark = (uintptr_t)marker;
		uint8_t adjustment = *((uint8_t*)(mark - 1));
		freeToRawUnaligned((void*)(mark - adjustment));
	}
}

void StackAllocator::clear()
{
	ASSERT(bottomMarker, "Tried to free stack to bottom when there is no memory allocated by stack");
	topMarker = bottomMarker;
}

void StackAllocator::reset()
{
	if (!bottomMarker) // already reseted
		return;

	::operator delete ((void*)(bottomMarker), sizeInBytes);
	bottomMarker = 0;
	topMarker = 0;
	sizeInBytes = 0;
}

bool StackAllocator::contains(void * ptr) const
{
	return ((uintptr_t)ptr >= bottomMarker && (uintptr_t)ptr < topMarker);
}

size_t StackAllocator::getSize() const
{
	return sizeInBytes;
}

size_t StackAllocator::getFreeSize() const
{
	if(sizeInBytes)
		return sizeInBytes - (topMarker - bottomMarker);
	return 0;
}

StackAllocator::StackAllocator(StackAllocator && rref)
{
	*this = std::move(rref);
}

StackAllocator & StackAllocator::operator=(StackAllocator && rref)
{
	topMarker = rref.topMarker;
	bottomMarker = rref.bottomMarker;
	sizeInBytes = rref.sizeInBytes;

	rref.topMarker = 0;
	rref.bottomMarker = 0;
	rref.sizeInBytes = 0;
	return *this;
}

StackAllocator::~StackAllocator()
{
	reset();
}