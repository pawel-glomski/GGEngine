#pragma once
#include <array>
#include "stdInclude.h"
#include <iostream>


// just a usual array, but with function that pushes elements behind last used largest index
template<class T, size_t size>
class Array
{
public:

	std::_Array_iterator<T, size> begin();

	std::_Array_iterator<T, size> end();

	std::_Array_const_iterator<T, size> begin() const;

	std::_Array_const_iterator<T, size> end() const;


	void push_back(const T& object);

	void push_back(T&& object);


	size_t currentSize() const;

	size_t maxSize() const;


	T& operator[](size_t pos);

	const T& operator[](size_t pos) const;

private:

	T elems[size];

	size_t count = 0;
};

template<class T, size_t size>
inline std::_Array_iterator<T, size> Array<T, size>::begin()
{
	return std::_Array_iterator<T, size>(elems, 0);
}

template<class T, size_t size>
inline std::_Array_iterator<T, size> Array<T, size>::end()
{
	return std::_Array_iterator<T, size>(elems, count);
}

template<class T, size_t size>
inline std::_Array_const_iterator<T, size> Array<T, size>::begin() const
{
	return std::_Array_const_iterator<T, size>(elems, 0);
}

template<class T, size_t size>
inline std::_Array_const_iterator<T, size> Array<T, size>::end() const
{
	return std::_Array_const_iterator<T, size>(elems, count);
}

template<class T, size_t size>
inline void Array<T, size>::push_back(const T & object)
{
	if (count + 1 <= size)
	{
		elems[count++] = object;
		return;
	}
	ASSERT((count + 1 <= size), "Tried to push object to full array!");
}

template<class T, size_t size>
inline void Array<T, size>::push_back(T && object)
{
	if (count + 1 <= size)
	{
		elems[count++] = std::move(object);
		return;
	}
	ASSERT((count + 1 <= size), "Tried to push object to full array!");
}

template<class T, size_t size>
inline size_t Array<T, size>::currentSize() const
{
	return count;
}

template<class T, size_t size>
inline size_t Array<T, size>::maxSize() const
{
	return size;
}

template<class T, size_t size>
inline T & Array<T, size>::operator[](size_t pos)
{
	if(pos < count)
		return elems[pos];
	else if(pos >= count && pos < size)
	{
		count = pos + 1;
		return elems[pos];
	}
	else
		throw std::out_of_range("");
}

template<class T, size_t size>
inline const T & Array<T, size>::operator[](size_t pos) const
{
	if (pos < count)
		return elems[pos];
	else if (pos >= count && pos < size)
	{
		count = pos + 1;
		return elems[pos];
	}
	else
		throw std::out_of_range("");
}