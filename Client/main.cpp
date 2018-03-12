#include <iostream>
#include "EntityModule.h"
#include "TransformComponent.h"

class TestEntity : public Entity<TransformComponent>
{
public:

	using Base_t = Entity<TransformComponent>;

	TestEntity(EntityId id) : Base_t(id) {}

	template<class U>
	void construct(U & entityModule)
	{
		Base_t::construct(entityModule);
		std::cout << "TestEntity construct";
	}
};



int main()
{
	EntityModule<Entity<TransformComponent>, TestEntity> emTest;

	emTest.spawnEntity<TestEntity>();
	emTest.update(1);
	//emTest.destroyEntity<Entity<TransformComponent>>(1);
	emTest.destroyEntity(1);

	

	return 0;
}