// Modified version of code:
// https://github.com/OneLoneCoder/videos/blob/master/OneLoneCoder_Splines2.cpp
// by Javidx9

#pragma once
#include <vector>
#include "MathUtilities.h"

class Spline
{
public:

	using Index_t = size_t;

	using PointsHolder_t = std::vector<Vec2f>;

public:

	Spline();

	template<class T>
	Spline(T&& points)
	{
		this->points = std::forward(points);
	}
	

	Vec2f pointFromSegment(Index_t segmentIndex, float_t alpha) const;

	Vec2f gradientFromSegment(Index_t segmentIndex, float_t alpha) const;


	Vec2f pointAt(float_t alpha) const;

	Vec2f gradientAt(float_t alpha) const;


	float_t getSegmentLength(Index_t segmentIndex) const;

	float_t getWholeLength() const;


	Vec2f& changePoint(Index_t index);

	void addPointAtEnd(const Vec2f& newPoint);

	void addPointAtIndex(Index_t index, const Vec2f& newPoint);

	void removePoint(Index_t index);


	const Vec2f& getPoint(Index_t index) const;

	const PointsHolder_t& getPoints() const;

	Index_t segmentsCount() const;

private:

	std::pair<Index_t, float_t> segmentAndAlphaAtIt(float_t globalAlpha) const;


private:

	PointsHolder_t points;


	mutable std::vector<float_t> segmentsLenghts;
	mutable bool updateLengths = true;
};

