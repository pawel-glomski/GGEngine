#include "MemoryManager.h"
#include "stdInclude.h"

void MemoryManager::startUp()
{
	PoolAllocator<CollidableEntity>::instance().init(5000);
	PoolAllocator<Projectile>::instance().init(5000);
	PoolAllocator<VisualEffect>::instance().init(5000);
	PoolAllocator<AudioEffect>::instance().init(200);
	stack.init((sizeof(Character) + alignof(Character)) * 20 );
}

void MemoryManager::shoutDown()
{
	PoolAllocator<CollidableEntity>::instance().reset();
	PoolAllocator<Projectile>::instance().reset();
	PoolAllocator<VisualEffect>::instance().reset();
	PoolAllocator<AudioEffect>::instance().reset();
	stack.reset();
}