#include "BinaryRelation.h"
#include "Pair.h"
#include <iostream>

using std::cerr;
using std::endl;

template<typename T, typename U>
inline Pair<T, U> BinaryRelation<T, U>::getPair(int index) const
{
	return this->elementsOfRelation[index];
}

template<typename T, typename U>
inline int BinaryRelation<T, U>::getSize() const
{
	return this->elementsOfRelation.size();
}

template<typename T, typename U>
inline void BinaryRelation<T, U>::addRelation(const Pair<T, U>& newRelation)
{
	this->elementsOfRelation.push_back(newRelation);
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::r(T t, U u) const
{
	Pair<T, U> newPair(t, u);
	
	return (checkRelation(newPair));
}

template<typename T, typename U>
inline BinaryRelation<U, T> BinaryRelation<T, U>::operator!()
{
	BinaryRelation<U, T> result;

	for (int i = 0; i < this->elementsOfRelation.size(); i++)
	{
		Pair<U, T> newPair(this->elementsOfRelation[i].getSecond(), this->elementsOfRelation[i].getFirst());
		result.addRelation(newPair);
	}

	return result;
}

template<typename T, typename U>
inline BinaryRelation<T, U> BinaryRelation<T, U>::operator+(BinaryRelation<T, U>& otherRelation)
{
	return BinaryRelation<T, U>(*this) += otherRelation;
}

template<typename T, typename U>
inline BinaryRelation<T, U> BinaryRelation<T, U>::operator^(BinaryRelation<T, U>& otherRelation)
{
	return BinaryRelation<T, U>(*this) ^= otherRelation;
}

template<typename T, typename U>
inline BinaryRelation<T, U>& BinaryRelation<T, U>::operator+=(BinaryRelation<T, U>& otherRelation)
{
	for (int i = 0; i < otherRelation.elementsOfRelation.size(); i++)
	{
		this->addRelation(otherRelation.elementsOfRelation[i]);
	}
	return (*this);
}

template<typename T, typename U>
inline BinaryRelation<T, U>& BinaryRelation<T, U>::operator^=(BinaryRelation<T, U>& otherRelation)
{
	BinaryRelation<T, U> temp;

	for (int i = 0; i < otherRelation.elementsOfRelation.size(); i++)
	{
		if (this->checkRelation(otherRelation.elementsOfRelation[i]))
		{
			temp.addRelation(otherRelation.elementsOfRelation[i]);
		}
	}
	/*for (int i = 0; i < this->elementsOfRelation.size(); i++)
	{
		this->elementsOfRelation.erase(elementsOfRelation.begin() + i);
	}*/
	*this = temp;
	return (*this);
}

template<typename T, typename U>
inline BinaryRelation<T, U>& BinaryRelation<T, U>::operator*=(BinaryRelation<U, U>& otherRelation)
{
	BinaryRelation<T, U> temp;

	for (int i = 0; i < this->elementsOfRelation.size(); i++)
	{
		for (int j = 0; j < otherRelation.getSize(); j++)
		{
			if (this->elementsOfRelation[i].getSecond() == otherRelation.getPair(j).getFirst())
			{
				Pair<T, U> newPair(this->elementsOfRelation[i].getFirst(), otherRelation.getPair(j).getSecond());
				temp.addRelation(newPair);
			}
		}
	}

	*this = temp;
	return (*this);
}

template<typename T, typename U>
inline vector<U> BinaryRelation<T, U>::operator[](const T& element)
{
	vector<U> result;

	for (int i = 0; i < this->elementsOfRelation.size(); i++)
	{
		if (this->elementsOfRelation[i].getFirst() == element)
		{
			result.push_back(this->elementsOfRelation[i].getSecond());
		}
	}

	if (result.size() == 0)
	{
		cerr << "There is no such element in the relation." << endl;
	}

	return result;
}

template<typename T, typename U>
inline vector<T> BinaryRelation<T, U>::operator()(const U& element)
{
	vector<T> result;

	for (int i = 0; i < this->elementsOfRelation.size(); i++)
	{
		if (this->elementsOfRelation[i].getSecond() == element)
		{
			result.push_back(this->elementsOfRelation[i].getFirst());
		}
	}

	if (result.size() == 0)
	{
		cerr << "There is no such element in the relation." << endl;
	}

	return result;
}

template<typename T, typename U>
inline vector<T> BinaryRelation<T, U>::dom()
{
	vector<T> result;

	int size = this->elementsOfRelation.size();

	for (int i = 0; i < size; i++)
	{
		result.push_back(elementsOfRelation[i].getFirst());
	}

	return result;
}

template<typename T, typename U>
inline vector<U> BinaryRelation<T, U>::ran()
{
	vector<U> result;
	for (int i = 0; i < this->elementsOfRelation.size(); i++)
	{
		result.push_back(elementsOfRelation[i].getSecond());
	}
	return result;
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::function() const
{
	for (int i = 0; i < this->elementsOfRelation.size(); i++)
	{
		for (int j = 0; j < this->elementsOfRelation.size(); j++)
		{
			if (this->elementsOfRelation[i].getFirst() == this->elementsOfRelation[j].getFirst() &&
				this->elementsOfRelation[i].getSecond() != this->elementsOfRelation[j].getSecond())
			{
				return false;
			}
		}
	}
	return true;
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::injection() const
{
	for (int i = 0; i < this->elementsOfRelation.size(); i++)
	{
		for (int j = 0; j < this->elementsOfRelation.size(); j++)
		{
			if (this->elementsOfRelation[i].getSecond() == this->elementsOfRelation[j].getSecind() &&
				this->elementsOfRelation[i].getFirst() != this->elementsOfRelation[j].getFirst())
			{
				return false;
			}
		}
	}
	return true;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const BinaryRelation<T, U>& relation) 
{
	if (relation.elementsOfRelation.size() == 0) 
	{
		out << "There are no relations yet." << endl;
	}
	else 
	{
		out << "Relations: ";

		unsigned size = relation.elementsOfRelation.size();

		for (int i = 0; i < size - 1; i++)
		{
			out << "(" << relation.getPair(i).getFirst() << ", " << relation.getPair(i).getSecond() << "), ";
		}

		out << "(" << relation.getPair(size - 1).getFirst() << ", " << relation.getPair(size - 1).getSecond() << ")" << endl;
	}

	return out;
}

template<typename T, typename U, typename V>
inline BinaryRelation<T, V> operator*(BinaryRelation<T, U>& lhs, BinaryRelation<U, V>& rhs)
{
	BinaryRelation<T, V> result;
	for (int i = 0; i < lhs.getSize(); i++)
	{
		for (int j = 0; j < rhs.getSize(); j++)
		{
			if (lhs.getPair(i).getSecond() == rhs.getPair(j).getFirst())
			{
				Pair<T, V> newPair(lhs.getPair(i).getFirst(), rhs.getPair(j).getSecond());
				result.addRelation(newPair);
			}
		}
	}
	
	return (result);
}

template<typename T, typename U>
inline bool BinaryRelation<T, U>::checkRelation(const Pair<T, U>& pair) const
{
	for (int i = 0; i < elementsOfRelation.size(); i++)
	{
		if (pair.getFirst() == elementsOfRelation[i].getFirst() &&
			pair.getSecond() == elementsOfRelation[i].getSecond())
		{
			return true; 
		}
	}

	return false; 
}
