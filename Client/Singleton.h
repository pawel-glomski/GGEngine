#pragma once

template<class T>
class Singleton
{
public:
	static T & instance()
	{
		static T inst;
		return inst;
	}
protected:
	Singleton() = default;
private:
	T & operator=(const Singleton& right) = delete;
	Singleton(const Singleton& right) = delete;
};