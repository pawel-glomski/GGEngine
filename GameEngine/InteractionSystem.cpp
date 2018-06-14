#include "InteractionSystem.h"
#include "DisplayComponent.h"

InteractionSystem::InteractionSystem(const ControllerModule & controllerModule) : controllerModule(controllerModule)
{
	cursor.r = 0;
}

void InteractionSystem::init(epp::EntityManager & entityManager)
{
	entityManager.requestCGroup(entities);
}

void InteractionSystem::update(epp::EntityManager & entityManager, float dt)
{
	drag();
	spawn(entityManager);
}

void InteractionSystem::drag()
{
	if (controllerModule.getActionKeyState(ActionKey::LMB) == KeyState::Pressed)
	{
		cursor.p = asVec<c2v>(controllerModule.getCursorWorldPosition());
		for (auto it = entities.begin(); it != entities.end(); ++it)
			if (it.getComponent<ShapeComponent>().getShape().isColliding(&cursor, C2_TYPE::C2_CIRCLE))
			{
				draggedEntity = it.getERef();
				break;
			}
	}
	else if (controllerModule.getActionKeyState(ActionKey::LMB) == KeyState::Released)
		draggedEntity = epp::EntityRef();

	if (draggedEntity.isValid())
	{
		Vec2f difference = controllerModule.getCursorWorldPosition() - draggedEntity.getComponent<TransformComponent>()->getPosition();
		float magnitude = difference.length() * 0.9f;
		magnitude *= magnitude;
		difference.normalize();
		draggedEntity.getComponent<PhysicsComponent>()->velocity *= 0.9f;
		draggedEntity.getComponent<PhysicsComponent>()->velocity += difference * magnitude;
	}
}

void InteractionSystem::spawn(epp::EntityManager & entityManager)
{
	if (controllerModule.getActionKeyState(ActionKey::RMB) != KeyState::Released)
	{
		for (int i = 0; i < 10; i++)
		{
			++spawnedCount;
			auto spawned = entityManager.spawn<TransformComponent, ShapeComponent, PhysicsComponent, DisplayComponent, CollisionComponent>();
			if (dist(rd) <= 2.f)
			{
				float a = 0.5f + dist(rd);
				float b = 0.5f + dist(rd);
				spawned.getComponent<ShapeComponent>()->takeShape<PolygonShape>().setAsBox(Vec2f(a, b));
				spawned.getComponent<PhysicsComponent>()->setMass(a * b);
				spawned.getComponent<PhysicsComponent>()->moi = 1.f / 12.f * a*b*(a*a + b * b);
				spawned.getComponent<PhysicsComponent>()->moiInv = 1.f / spawned.getComponent<PhysicsComponent>()->moi;
				spawned.getComponent<TransformComponent>()->setPosition(controllerModule.getCursorWorldPosition());
			}
			else
			{

				float r = 0.5f + dist(rd);
				spawned.getComponent<ShapeComponent>()->takeShape<CircleShape>().setRadius(r);
				spawned.getComponent<PhysicsComponent>()->setMass(PI_F*r*r);
				spawned.getComponent<PhysicsComponent>()->moi = 1.f / 2.f * PI_F*r*r*r*r;
				spawned.getComponent<PhysicsComponent>()->moiInv = 1.f / spawned.getComponent<PhysicsComponent>()->moi;
				spawned.getComponent<TransformComponent>()->setPosition(controllerModule.getCursorWorldPosition());
			}
		}
	}
	std::cout << spawnedCount << std::endl;
}
