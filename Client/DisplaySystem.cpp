#include "DisplaySystem.h"
#include "stdInclude.h"
#include "EntityManager.h"
#include "Character.h"



void DisplaySystem::update(float_t dt)
{
	drawWorldStaticEntities();
	drawDynamicEntities();
}

void DisplaySystem::drawWorldStaticEntities()
{
	auto camPos = camera.lock()->getComponent<TransformComponent>()->getGlobalPosition();
	camPos += Vec2f(sign(camPos.x), sign(camPos.y)) * gridSize;
	camPos /= gridSize;

	Vec2i minIndices = Vec2i(camPos) - (Vec2i(DisplaySettings::ViewResolution / DisplaySettings::WorldToWindowRatio / gridSize / 2.f + Vec2f(0.5, 0.5)));
	Vec2i maxIndices = Vec2i(camPos) + (Vec2i(DisplaySettings::ViewResolution / DisplaySettings::WorldToWindowRatio / gridSize / 2.f + Vec2f(0.5, 0.5)));

	if (camPos.x > 0 && camPos.x < DisplaySettings::ViewResolution.x / DisplaySettings::WorldToWindowRatio / gridSize / 2.f)
		minIndices.x--;
	else if (camPos.x > -DisplaySettings::ViewResolution.x / DisplaySettings::WorldToWindowRatio / gridSize / 2.f)
		maxIndices.x++;
	if (camPos.y > 0 && camPos.y < DisplaySettings::ViewResolution.y / DisplaySettings::WorldToWindowRatio / gridSize / 2.f)
		minIndices.y--;
	else if (camPos.y > -DisplaySettings::ViewResolution.y / DisplaySettings::WorldToWindowRatio / gridSize / 2.f)
		maxIndices.y++;

	for (int32_t x = minIndices.x; x <= maxIndices.x; x++)
		for (int32_t y = minIndices.y; y <= maxIndices.y; y++)
			if (entityGrid.count(Vec2i(x, y)))
				for (auto & entityId : entityGrid[Vec2i(x, y)])
					drawEntity(entityId);
}

void DisplaySystem::drawDynamicEntities()
{
	auto camPos = camera.lock()->getComponent<TransformComponent>()->getGlobalPosition();
	if (entitiesToUpdate)
		for (auto & entityNode : *entitiesToUpdate)
			if ((camPos - entityNode.second->getComponent<TransformComponent>()->getGlobalPosition()).length() > (DisplaySettings::ViewResolution / 2.f).length())
				continue;
			else
				drawEntity(*entityNode.second);
}

void DisplaySystem::drawEntity(const Entity & entity)
{
	auto disComp = entity.getComponent<DisplayComponent>();
	auto trComp = entity.getComponent<TransformComponent>();
	sf::RenderStates states;
	states.transform.translate(trComp->getGlobalPosition().asSfVec()  * DisplaySettings::WorldToWindowRatio);
	states.transform.rotate(toDegrees(trComp->getGlobalRotation()));
	states.transform.scale(trComp->getGlobalScale().asSfVec() * DisplaySettings::WorldToWindowRatio);
	displayLayers[(uint8_t)disComp->getDisplayLevel()].draw(disComp->getShape(), states);
}

void DisplaySystem::addEntity(const EntityManager::EntityPtr & entity, const std::shared_ptr<EntityManager::EntityContainer> & everyEntityContainer)
{
	if (auto displayComponent = entity->getComponent<DisplayComponent>())
	{
		auto transformComponent = entity->getComponent<TransformComponent>();
		if(transformComponent->getMobility() != TransformComponent::Mobility::WorldStatic)
			EntityUpdateSystem::addEntity(entity, everyEntityContainer);
		else
		{
			auto bounds = displayComponent->getShape().getBounds();

			Vec2i topLeft = Vec2i(Vec2f(bounds.left, bounds.top) + transformComponent->getGlobalPosition()) / (int32_t)gridSize;
			topLeft += Vec2i(sign(topLeft.x), sign(topLeft.y));

			Vec2i size = Vec2i((int32_t)std::ceil(bounds.width / gridSize), (int32_t)std::ceil(bounds.height / gridSize));

			for(int32_t x = topLeft.x; x <= topLeft.x + size.x; x++)
				for(int32_t y = topLeft.y; y <= topLeft.y + size.y; y++)
					if(x && y)
						entityGrid[Vec2i(x,y)][entity->getID()] = entity;
		}
	}
}

void DisplaySystem::removeEntity(const Entity::ID & entity)
{

}

void DisplaySystem::reset()
{
	EntityUpdateSystem::reset();
	entityGrid.clear();
}

void DisplaySystem::setCamera(const std::shared_ptr<Entity>& camera)
{
	ASSERT(camera, "Tried to set camera to nullptr");
	if (camera)
		this->camera = std::static_pointer_cast<Camera>(camera);
}

