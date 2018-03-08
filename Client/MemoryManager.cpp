#include "MemoryManager.h"
#include "stdInclude.h"
#include "Character.h"
#include "Obstacle.h"
#include "Camera.h"

StackAllocator MemoryManager::stack;
std::unordered_map<std::type_index, Pool> MemoryManager::pools;


	
void MemoryManager::startUp()
{
	initNewPool<Character>(10000);
	initNewPool<Obstacle>(10000);
	initNewPool<Camera>(10);

	stack.init(1024000);

}

void MemoryManager::shoutDown()
{
	pools[std::type_index(typeid(Character))].reset();

	stack.reset();
}

void MemoryManager::clearPools()
{
	for (auto & pool : pools)
		pool.second.clear();
}
