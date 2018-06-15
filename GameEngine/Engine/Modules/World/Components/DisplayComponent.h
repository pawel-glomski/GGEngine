#pragma once
#include "Modules/Display/DisplayLayer.h"
#include "Modules/World/Components/ShapeComponent.h"


class DisplayShape : public sf::Drawable
{
protected:

	DisplayShape(C2_TYPE shapeType);

public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual bool copyConfiguration(const ShapeBase& shape) = 0;


	C2_TYPE getType() const;


private:

	C2_TYPE type;

};




class CircleDisplayShape : public DisplayShape
{
public:

	CircleDisplayShape();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual bool copyConfiguration(const ShapeBase& shape) override;

	void setRadius(float radius);

private:

	sf::VertexArray shape;

	float radius = 1.f;
};




class PolygonDisplayShape : public DisplayShape
{
public:

	PolygonDisplayShape();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual bool copyConfiguration(const ShapeBase& shape) override;

	template<class T>
	void setupVertices(const T* vertices, int32_t count)
	{
		shape.clear();
		if(count)
			for (int32_t i = 0; i <= count; ++i)
				shape.append(asVec<sf::Vector2f>(*(vertices + i % count)));
	}

	const sf::VertexArray& getVertexArray() const;

private:

	sf::VertexArray shape;
};




class DisplayComponent : public epp::Component
{

public:

	DisplayComponent();


	void takeShape(const ShapeBase& shape);


	void setDisplayLevel(DisplayLayer::Level level);


	DisplayShape& getShape();

	const DisplayShape& getShape() const;

	DisplayLayer::Level getDisplayLevel() const;

private:

	std::unique_ptr<DisplayShape> displayShape;

	DisplayLayer::Level displayLevel = DisplayLayer::Level::Bottom;
};
