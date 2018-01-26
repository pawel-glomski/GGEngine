#pragma once

template<class T>
class Singleton
{
public:
	static T& instance();

protected:
	Singleton() {};
	Singleton(const Singleton<T>&) = delete;
	Singleton<T>& operator=(const Singleton<T> &) = delete;
};

template<class T>
inline T & Singleton<T>::instance()
{
	static T inst;
	return inst;
}
