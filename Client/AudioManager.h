#pragma once
#include <cstdint>
#include <corecrt_math.h>

struct AudioSettings
{
	float_t generalVolume;
	float_t musicVolume;
	float_t abilitiesVolume;
	float_t communicationSoundsVolume;
};

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
};

