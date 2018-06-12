#pragma once
#include <ECSpp/System.h>
#include "DisplayModule.h"
#include "TransformComponent.h"
#include "ShapeComponent.h"
#include "DisplayComponent.h"

class DisplaySystem : public epp::System
{
public:

	DisplaySystem(DisplayModule& displayModule);

	virtual void init(epp::EntityManager& entityManager) override;

	virtual void update(epp::EntityManager& entityManager, float dt) override;

private:

	DisplayModule& displayModule;

	epp::CGroup<DisplayComponent, TransformComponent, ShapeComponent> entities;
};