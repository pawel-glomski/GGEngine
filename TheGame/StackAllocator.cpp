#include "stdInclude.h"
#include "StackAllocator.h"

StackAllocator::StackAllocator(uint32_t sizeInBytes)
{
	this->sizeInBytes = sizeInBytes;
	bottomMarker = (uint32_t)(new char[sizeInBytes]);
	topMarker = bottomMarker;
}

void * StackAllocator::allocUnaligned(uint32_t sizeInBytes)
{
	if (topMarker + sizeInBytes <= bottomMarker + this->sizeInBytes)
	{
		topMarker += sizeInBytes;
		return (void*)(topMarker - sizeInBytes);
	}
	ASSERT(false, "Not enough memory to allocate more!");
	return nullptr;
}

void * StackAllocator::allocAligned(uint32_t sizeInBytes, uint8_t alignment)
{
	ASSERT((alignment & (alignment - 1)) == 0, "Alignment is not power of 2");

	uint32_t rawAddress = (uint32_t)allocUnaligned(sizeInBytes + alignment);
	if (!rawAddress)
		return nullptr;
	uint32_t mask = (alignment - 1);
	uint8_t misalignment = (rawAddress & mask);
	uint8_t adjustment = alignment - misalignment;
	uint32_t alignedAddress = rawAddress + adjustment;

	uint8_t* pAdjustment = (uint8_t*)(alignedAddress - 1);
	*pAdjustment = adjustment;

	return (void*)alignedAddress;
}

StackAllocator::Marker StackAllocator::getMarker() const
{
	return topMarker;
}

void StackAllocator::freeToMarkerUnaligned(Marker marker)
{
	ASSERT((marker < topMarker), "Tried to free memory to a marker that lies further than stack's top marker")
	if(marker < topMarker)
		topMarker = marker;
}

void StackAllocator::freeToMarkerAligned(Marker marker)
{
	uint8_t adjustment = *((uint8_t*)(marker - 1));
	freeToMarkerUnaligned(marker - adjustment);
}