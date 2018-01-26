#include "MemoryManager.h"
#include "stdInclude.h"

void MemoryManager::startUp()
{
	PoolAllocator<Character>::instance().init(200);
	PoolAllocator<CollidableEntity>::instance().init(200);
	PoolAllocator<Projectile>::instance().init(200);
	PoolAllocator<VisualEffect>::instance().init(200);
	PoolAllocator<AudioEffect>::instance().init(200);
	stack.init(2048);
}

void MemoryManager::shoutDown()
{
	PoolAllocator<Character>::instance().reset();
	PoolAllocator<CollidableEntity>::instance().reset();
	PoolAllocator<Projectile>::instance().reset();
	PoolAllocator<VisualEffect>::instance().reset();
	PoolAllocator<AudioEffect>::instance().reset();
	stack.reset();
}