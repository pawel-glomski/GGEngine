#pragma once
#include <ECSpp/Component.h>
#include "DisplayLayer.h"
#include "ShapeComponent.h"


namespace sf
{
	class PolygonShape : public sf::Shape
	{
	public:

		template<class T>
		void setupVertices(const T* vertices, int32_t count)
		{
			ASSERT((count <= C2_MAX_POLYGON_VERTS), "Vertices count cannot be greater b2_maxPolygonVertices!");
			ASSERT((sizeof(Vec2f) == sizeof(T)), "Different sizes of vector types!");

			count = minValue(count, C2_MAX_POLYGON_VERTS);

			verticesCount = uint8_t(count);
			memcpy(this->vertices, vertices, count * sizeof(Vec2f));
			update();
		}
	

		virtual std::size_t getPointCount() const override;

		virtual Vector2f getPoint(std::size_t index) const override;


	private:

		Vec2f vertices[C2_MAX_POLYGON_VERTS];

		uint8_t verticesCount = 0;
	};
}




class DisplayShape : public sf::Drawable
{
protected:

	DisplayShape(sf::Shape& shape, C2_TYPE shapeType);

public:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	virtual bool copyConfiguration(const ShapeBase& shape) = 0;


	void copyConfiguration(const sf::Shape& shape);


	C2_TYPE getType() const;

	const sf::Shape& getSfShape() const;


private:

	sf::Shape& shapeRef;

	C2_TYPE type;

};




class CircleDisplayShape : public DisplayShape
{
public:

	CircleDisplayShape();

	virtual bool copyConfiguration(const ShapeBase& shape) override;

private:

	sf::CircleShape shape;

};




class PolygonDisplayShape : public DisplayShape
{
public:

	PolygonDisplayShape();

	virtual bool copyConfiguration(const ShapeBase& shape) override;

private:

	sf::PolygonShape shape;

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
