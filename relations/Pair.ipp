#include "Pair.h"

template<typename T, typename U>
Pair<T, U>::Pair(const T& first, const U& second)
{
	this->first = first;
	this->second = second;
}

template<typename T, typename U>
inline T Pair<T, U>::getFirst() const
{
	return this->first;
}

template<typename T, typename U>
inline void Pair<T, U>::setFirst(const T& newFirst)
{
	this->first = newFirst;
}

template<typename T, typename U>
inline U Pair<T, U>::getSecond() const
{
	return this->second;
}

template<typename T, typename U>
inline void Pair<T, U>::setSecond(const U& newSecond)
{
	this->second = newSecond;
}