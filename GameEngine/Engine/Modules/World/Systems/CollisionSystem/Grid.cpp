#include "Grid.h"


void Grid::setGridSize(float size)
{
	gridSize = size;
}

void Grid::insert(const RefType & it)
{
	const Vec2f& pos = it.getComponent<TransformComponent>().getPosition();
	const AABB& aabb = it.getComponent<ShapeComponent>().getShape().getAABB();

	Vec2i minIndices = posAsIndices(aabb.min + pos);
	Vec2i maxIndices = posAsIndices(aabb.max + pos);

	for (ptrdiff_t x = minIndices.x; x <= maxIndices.x; ++x)
		for (ptrdiff_t y = minIndices.y; y <= maxIndices.y; ++y)
			if (x == 0 || y == 0)
				continue;
			else
				cells[Vec2i(x, y)].push_back(it);
}

const std::vector<const std::vector<Grid::RefType>*>& Grid::queryFor(const Vec2f& pos, const AABB& aabb)
{
	queryResult.clear();
	Vec2i minIndices = posAsIndices(aabb.min + pos);
	Vec2i maxIndices = posAsIndices(aabb.max + pos);
	
	for (ptrdiff_t x = minIndices.x; x <= maxIndices.x; ++x)
		for (ptrdiff_t y = minIndices.y; y <= maxIndices.y; ++y)
			if (auto found = cells.find(Vec2i(x, y)); found != cells.end())
				queryResult.push_back(&found->second);
	return queryResult;
}

Vec2i Grid::posAsIndices(const Vec2f & pos) const
{
	return Vec2i(	ptrdiff_t(std::ceil(abs(pos.x) / gridSize)) * sign(pos.x), 
					ptrdiff_t(std::ceil(abs(pos.y) / gridSize)) * sign(pos.y)	);
}

void Grid::clear()
{
	cells.clear();
}

float Grid::getGridSize() const
{
	return gridSize;
}

const Grid::CellsHolder_t & Grid::getCells() const
{
	return cells;
}

