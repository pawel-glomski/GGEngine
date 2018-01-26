
template<class T>
template<class U>
inline Vect2<T>::Vect2(const Vect2<U>& vec) : x(T(vec.x)), y(T(vec.y))
{
}

template<class T>
template<typename U>
inline Vect2<T>::Vect2(const sf::Vector2<U>& vec) : x(T(vec.x)), y(T(vec.y))
{
}

template<class T>
inline Vect2<T>::Vect2(T x, T y) : x(x), y(y)
{
}

template<class T>
inline Vect2<T>::Vect2() : x(0), y(0)
{
}

template<class T>
inline T Vect2<T>::length() const
{
	return sqrt(x * x + y * y);
}

template<class T>
inline Vect2<T> Vect2<T>::normalized() const
{
	return Vect2<T>(*this).normalize();
}

template<class T>
inline Vect2<T>& Vect2<T>::normalize()
{
	T leng = length();
	if (leng)
	{
		x /= leng;
		y /= leng;
	}

	return *this;
}

////////////////////////////////////////////////////////// operators //////////////////////////////////////////////////////////

template<class T>
template<typename U>
inline Vect2<T>& Vect2<T>::operator=(const sf::Vector2<U>& sfVector)
{
	x = sfVector.x;
	y = sfVector.y;
	return *this;
}

template<class T>
inline Vect2<T> operator+(const Vect2<T> & left, const Vect2<T> & right)
{
	return Vect2<T>(left.x + right.x, left.y + right.y);
}

template<class T>
inline Vect2<T> operator-(const Vect2<T> & left, const Vect2<T> & right)
{
	return Vect2<T>(left.x - right.x, left.y - right.y);
}

template<class T>
inline Vect2<T> operator-(const Vect2<T> & right)
{
	return Vect2<T>(-right.x, -right.y);
}

template<class T, class U>
inline Vect2<T> operator*(const Vect2<T> & left, U right)
{
	return Vect2<T>(left.x * right, left.y * right);
}

template<class T, class U>
inline Vect2<T> operator*(U left, const Vect2<T> & right)
{
	return Vect2<T>(left * right.x, left * right.y);
}

// if right == 0, returns zero vector
template<class T>
inline Vect2<T> operator/(const Vect2<T> & left, T right)
{
	if (right)
		return Vect2<T>(left.x / right, left.y / right);
	else
		return Vect2<T>();
}

template<class T>
inline Vect2<T> operator/(T left, const Vect2<T> & right)
{
	return Vect2<T>(right.x != 0 ? left / right.x : 0, right.y != 0 ? left / right.y : 0);
}

template<class T>
inline Vect2<T>& operator+=(Vect2<T> & left, const Vect2<T> & right)
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

template<class T>
inline Vect2<T>& operator-=(Vect2<T> & left, const Vect2<T> & right)
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

template<class T>
inline Vect2<T>& operator*=(Vect2<T> & left, T right)
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

// if right == 0, returns zero vector
template<class T>
inline Vect2<T>& operator/=(Vect2<T> & left, T right)
{
	if (right)
	{
		left.x /= right;
		left.y /= right;
	}
	else
		left = Vect2<T>();
	return left;
}



template<class T>
inline bool operator==(const Vect2<T> & left, const Vect2<T> & right)
{
	return left.x == right.x && left.y == right.y;
}

template<class T>
inline bool operator!=(const Vect2<T> & left, const Vect2<T> & right)
{
	return !(left == right);
}


template<class T>
std::ostream& operator<<(std::ostream& os, const Vect2<T>& v)
{
	os.precision(3);
	os.setf(std::ios::fixed);
	os << "x: " << std::setprecision(3) << std::setw(10) << v.x << "   ";
	os << "y: " << std::setprecision(3) << std::setw(10) << v.y << "   ";
	os << std::endl;
	return os;
}