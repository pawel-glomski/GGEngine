#pragma once
#include <stdint.h>

class StackAllocator
{
	typedef uint32_t Marker;

public:
	explicit StackAllocator(uint32_t sizeInBytes);

	void* allocUnaligned(uint32_t sizeInBytes);

	//  "alignment" must be a power of 2
	void* allocAligned(uint32_t sizeInBytes, uint8_t alignment);

	Marker getMarker() const;

	void freeToMarkerUnaligned(Marker marker);
	void freeToMarkerAligned(Marker marker);

private:
	Marker topMarker;
	Marker bottomMarker;
	uint32_t sizeInBytes;
};
