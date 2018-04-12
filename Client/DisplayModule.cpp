#include "DisplayModule.h"

void DisplayModule::update(float_t dt)
{
	updateView();
	displayLayers();
}

void DisplayModule::updateView()
{
	if (auto transformToReach = followingTransformC.lock())
	{
		auto & window = getDependency<WindowModule>().getWin();
		sf::View newView = window.getView();

		newView.setCenter((transformToReach->getGlobalPosition() * Settings<WindowModule>::WorldToViewRatio).asSfVec());
		//newView.setSize((Settings<WindowModule>::ViewResolution * 10.f).asSfVec());

		window.setView(newView);
	}
}

void DisplayModule::displayLayers()
{
	auto & window = getDependency<WindowModule>().getWin();

	window.clear();

	for (auto & layer : layers)
		layer.display(window);

	window.display();
}

void DisplayModule::drawWorldObject(const sf::Drawable & object, const Transform & transform, DisplayLayer::Level level)
{
	sf::RenderStates states;

	states.transform.translate(transform.position.asSfVec() * Settings<WindowModule>::WorldToViewRatio);
	states.transform.rotate((toDegrees(transform.rotation)));
	states.transform.scale(transform.scaleV.asSfVec() * Settings<WindowModule>::WorldToViewRatio);

	layers[(uint8_t)level].draw(object, states);
}

void DisplayModule::drawWindowObject(const sf::Drawable & object, DisplayLayer::Level level)
{
	layers[(uint8_t)level].draw(object);
}

void DisplayModule::setWatchedEntity(const CPtr_t<TransformComponent>& watchedEntityTransform)
{
	ASSERT(watchedEntityTransform, "Tried to set to follow nullptr");
	if (watchedEntityTransform)
		followingTransformC = watchedEntityTransform;
}