#include "Spline.h"
#include <ECSpp/Utility/DebugAssert.h>


Spline::Spline()
{
	points = { {-1.f, -2.f}, { 0.f, -1.f }, { 0.f, 1.f }, { 1.f, 2.f } };
}

Vec2f Spline::pointFromSegment(Index_t segmentIndex, float_t t) const
{
	ASSERT((segmentIndex < segmentsCount()), "Invalid segment index, returning zero vector");
	if (segmentIndex >= segmentsCount())
		return Vec2f::ZeroVector;

	int p0 = int(segmentIndex);
	int p1 = p0 + 1;
	int p2 = p1 + 1;
	int p3 = p2 + 1;

	float tt = t * t;
	float ttt = tt * t;

	float q1 = -ttt + 2.0f*tt - t;
	float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
	float q3 = -3.0f*ttt + 4.0f*tt + t;
	float q4 = ttt - tt;

	float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
	float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

	return { tx, ty };
}

Vec2f Spline::gradientFromSegment(Index_t segmentIndex, float_t t) const
{
	ASSERT((segmentIndex < segmentsCount()), "Invalid segment index, returning zero vector");
	if (segmentIndex >= segmentsCount())
		return Vec2f::ZeroVector;

	int p0 = int(segmentIndex);
	int p1 = p0 + 1;
	int p2 = p1 + 1;
	int p3 = p2 + 1;

	float tt = t * t;
	float ttt = tt * t;


	float q1 = -3.0f * tt + 4.0f*t - 1;
	float q2 = 9.0f*tt - 10.0f*t;
	float q3 = -9.0f*tt + 8.0f*t + 1.0f;
	float q4 = 3.0f*tt - 2.0f*t;

	float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
	float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

	return { tx, ty };
}

Vec2f Spline::pointAt(float_t alpha) const
{
	clamp(alpha, 0.f, 1.f);

	auto segmentANDalpha = segmentAndAlphaAtIt(alpha);

	return pointFromSegment(segmentANDalpha.first, segmentANDalpha.second);
}

Vec2f Spline::gradientAt(float_t alpha) const
{
	clamp(alpha, 0.f, 1.f);

	auto segmentANDalpha = segmentAndAlphaAtIt(alpha);

	return gradientFromSegment(segmentANDalpha.first, segmentANDalpha.second);
}

std::pair<Spline::Index_t, float_t> Spline::segmentAndAlphaAtIt(float_t alpha) const
{
	float_t lengthAtPoint = getWholeLength() * alpha;
	Index_t rightSegment = 0;
	float_t rightSegmentLength = getSegmentLength(0);
	float_t lengthsSum = rightSegmentLength;

	for (Index_t i = 1; i < segmentsCount(); i++)
		if (lengthsSum >= lengthAtPoint)
		{
			rightSegment = i - 1;
			break;
		}
		else
		{
			rightSegmentLength = getSegmentLength(i);
			lengthsSum += rightSegmentLength;
		}

	alpha = (lengthAtPoint - (lengthsSum - rightSegmentLength)) / rightSegmentLength;

	return std::pair<Index_t, float_t>(rightSegment, alpha);
}

float_t Spline::getSegmentLength(Index_t segmentIndex) const
{
	ASSERT((segmentIndex < segmentsCount()), "Invalid segment index, returning zero");
	if (segmentIndex >= segmentsCount())
		return 0;

	if (updateLengths)
	{
		for (size_t i = 0; i < segmentsCount(); i++)
		{
			float_t length = 0.f;
			Vec2f last = getPoint(i + 1);
			Vec2f current;
			for (float_t i = 0.005f; i <= 1.f; i += 0.005f)
			{
				current = last + pointAt(i);
				length += (current - last).length();
				last = current;
			}
			segmentsLenghts[i] = length;
		}
		updateLengths = false;
	}

	return segmentsLenghts[segmentIndex];
}

float_t Spline::getWholeLength() const
{
	float_t wholeLength = 0.f;
	for (size_t i = 0; i < segmentsCount(); i++)
		wholeLength += getSegmentLength(i);

	return wholeLength;
}

Vec2f & Spline::changePoint(Index_t index)
{
	ASSERT((index < points.size()), "Index out of range");
	updateLengths = true;
	return points[index];
}

void Spline::addPointAtEnd(const Vec2f & newPoint)
{
	addPointAtIndex(points.size(), newPoint);
}

void Spline::addPointAtIndex(Index_t index, const Vec2f & newPoint)
{
	ASSERT((index <= points.size()), "Index out of range");
	PointsHolder_t::const_iterator pos = points.begin() + index;
	points.insert(pos, newPoint);
	
	updateLengths = true;
}

void Spline::removePoint(Index_t index)
{
	ASSERT((points.size() > 4), "Spline is already at minimal points count, cannot remove more from it");
	if (points.size() > 4)
	{
		ASSERT((index < points.size()), "Index out of range");
		PointsHolder_t::const_iterator pos = points.begin() + index;
		points.erase(pos);
		updateLengths = true;
	}
}

const Vec2f & Spline::getPoint(Index_t index) const
{
	ASSERT((index < points.size()), "Index out of range");
	return points[index];
}

const Spline::PointsHolder_t & Spline::getPoints() const
{
	return points;
}

Spline::Index_t Spline::segmentsCount() const
{
	return points.size() - 3;
}