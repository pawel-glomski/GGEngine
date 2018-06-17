
template<class T>
template<class U>
inline Vec2<T>::Vec2(const Vec2<U>& vec) : x(T(vec.x)), y(T(vec.y))
{
}

template<class T>
inline Vec2<T>::Vec2(T x, T y) : x(x), y(y)
{
}

template<class T>
inline Vec2<T>::Vec2() : x(0), y(0)
{
}

template<class T>
inline T Vec2<T>::length() const
{
	return T(sqrtf(x * x + y * y));
}

template<class T>
inline Vec2<T> Vec2<T>::normalized() const
{
	return Vec2<T>(*this).normalize();
}

template<class T>
inline Vec2<T>& Vec2<T>::normalize()
{
	T leng = length();
	if (leng)
	{
		x /= leng;
		y /= leng;
	}

	return *this;
}

template<class T>
inline Vec2<T>& Vec2<T>::clamp(const Vec2<T> minValues, const Vec2<T> maxValues)
{
	::clamp(x, minValues.x, maxValues.x);
	::clamp(y, minValues.y, maxValues.y);
	return *this;
}

template<class T>
inline Vec2<T>& Vec2<T>::clamp(float maxLength)
{
	float len = length();
	if (len > maxLength)
		*this *= maxLength / len;
	return *this;
}

////////////////////////////////////////////////////////// operators //////////////////////////////////////////////////////////

template<class T>
inline Vec2<T> operator+(const Vec2<T> & left, const Vec2<T> & right)
{
	return Vec2<T>(left.x + right.x, left.y + right.y);
}

template<class T>
inline Vec2<T> operator-(const Vec2<T> & right)
{
	return Vec2<T>(-right.x, -right.y);
}

template<class T>
inline Vec2<T> operator-(const Vec2<T> & left, const Vec2<T> & right)
{
	return left + (-right);
}

template<class T>
inline Vec2<T> operator*(const Vec2<T> & left, T right)
{
	return Vec2<T>(left.x * right, left.y * right);
}

template<class T>
inline Vec2<T> operator*(T left, const Vec2<T> & right)
{
	return right * left;
}

// if right == 0, returns zero vector
template<class T>
inline Vec2<T> operator/(const Vec2<T> & left, T right)
{
	ASSERT(right, "Vector division by 0");
	if (right)
		return Vec2<T>(left.x / right, left.y / right);
	else
		return Vec2<T>();
}
// if one of vector's components == 0, in returned vector that component value will also be 0 
template<class T>
inline Vec2<T> operator/(T left, const Vec2<T> & right)
{
	ASSERT(right.x, "Vector division by 0");
	ASSERT(right.y, "Vector division by 0");
	return Vec2<T>(right.x != 0 ? left / right.x : 0, right.y != 0 ? left / right.y : 0);
}

template<class T>
inline Vec2<T>& operator+=(Vec2<T> & left, const Vec2<T> & right)
{
	return left = (left + right);
}

template<class T>
inline Vec2<T>& operator-=(Vec2<T> & left, const Vec2<T> & right)
{
	return left = (left - right);
}

template<class T>
inline Vec2<T>& operator*=(Vec2<T> & left, T right)
{
	return left = (left * right);
}

// if right == 0, returns zero vector
template<class T>
inline Vec2<T>& operator/=(Vec2<T> & left, T right)
{
	ASSERT(right, "Vector division by 0");
	if (right)
	{
		left.x /= right;
		left.y /= right;
	}
	else
		left = Vec2<T>::ZeroVector;
	return left;
}



template<class T>
inline bool operator==(const Vec2<T> & left, const Vec2<T> & right)
{
	return left.x == right.x && left.y == right.y;
}

template<class T>
inline bool operator!=(const Vec2<T> & left, const Vec2<T> & right)
{
	return !(left == right);
}


template<class T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v)
{
	os.precision(3);
	os.setf(std::ios::fixed);
	os << "x: " << v.x << "   ";
	os << "y: " << v.y << "   ";
	os << std::endl;
	return os;
}

// utilities

template<class T>
inline float_t dotProduct(const Vec2<T>& vec1, const Vec2<T>& vec2)
{
	return float_t(vec1.x * vec2.x + vec1.y * vec2.y);
}

template<class T>
inline float_t crossProduct(const Vec2<T>& vec1, const Vec2<T>& vec2)
{
	return float_t(vec1.x*vec2.y - vec1.y*vec2.x);
}

template<class T>
inline float_t angleBetweenVectors(Vec2<T> vec1, Vec2<T> vec2)
{
	vec1.normalize();
	vec2.normalize();
	return atan2(crossProduct(vec1, vec2), dotProduct(vec1, vec2));
}
