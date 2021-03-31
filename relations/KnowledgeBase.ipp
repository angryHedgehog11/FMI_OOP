#include "KnowledgeBase.h"
#include "Pair.h"
#include "BinaryRelation.h"
#include <string>
#include <vector>

template<typename T, typename U>
inline void KnowledgeBase<T, U>::addNewRelation(const string& relationName, const BinaryRelation<T, U>& newRelation)
{
	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		if (this->knowledgeVector[i].first == relationName)
		{
			cout << "Already exists a relation with this name." << endl;
			return; 
		}
	}

	knowledgeVector.push_back(std::make_pair(relationName, newRelation));
}

template<typename T, typename U>
inline void KnowledgeBase<T, U>::addMemberToRealation(const string& name, const Pair<T, U>& newMember)
{
	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		if (this->knowledgeVector[i].first == name)
		{
			this->knowledgeVector[i].second.addRelation(newMember); 
		}
	}
}

template<typename T, typename U>
inline bool KnowledgeBase<T, U>::r(const string& name, const Pair<T, U> checkRelation) const
{
	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		if ((knowledgeVector[i].getName().compare(name)) != 0)
		{
			return false;
		}
		else
		{
			return (knowledgeVector[i].r(checkRelation.getFirst(), checkRelation.getSecond()));
		}
	}
}

template<typename T, typename U>
inline vector<T> KnowledgeBase<T, U>::operator()(U u) const
{
	vector<T> result; 

	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		vector<T> temp = this->knowledgeVector[i].second(u); 

		for (int j = 0; j < temp.size(); j++)
		{
			bool alreadyExists = false; 

			for (int k = 0; k < result.size(); k++)
			{
				if (temp[j] == result[k])
				{
					alreadyExists = true;
					break; 
				}
			}

			if (alreadyExists == false)
			{
				result.push_back(temp[j]);
			}
		}
	}

	return result; 
}

template<typename T, typename U>
inline vector<U> KnowledgeBase<T, U>::operator[](T t) const
{
	vector<U> result;

	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		vector<U> temp = this->knowledgeVector[i].second[t];

		for (int j = 0; j < temp.size(); j++)
		{
			bool alreadyExists = false; 

			for (int k = 0; k < result.size(); k++)
			{
				if (temp[j] == result[k])
				{
					alreadyExists = true; 
					break; 
				}
			}

			if (alreadyExists == false)
			{
				result.push_back(temp[j]);
			}
		}
	}

	return result; 
}

template<typename T, typename U>
inline std::vector<T> KnowledgeBase<T, U>::dom() const
{
	vector<T> result;

	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		vector<T> temp = this->knowledgeVector[i].second.dom();

		for (int j = 0; j < temp.size(); j++)
		{
			bool alreadyExists = false; 

			for (int k = 0; k < result.size(); k++)
			{
				if (temp[j] == result[k])
				{
					alreadyExists = true; 
					break; 
				}
			}

			if (alreadyExists == false)
			{
				result.push_back(temp[j]);
			}
		}
	}

	return result;
}

template<typename T, typename U>
inline std::vector<U> KnowledgeBase<T, U>::ran() const
{
	vector<U> result; 
	
	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		vector<U> temp = this->knowledgeVector[i].second.ran(); 

		for (int j = 0; j < temp.size(); j++)
		{
			bool alreadyExists = false; 

			for (int k = 0; k < result.size(); k++)
			{
				if (temp[j] == result[k])
				{
					alreadyExists = true; 
					break; 
				}
			}

			if (alreadyExists == false)
			{
				result.push_back(temp[j]);
			}
		}
	}

	return result; 
}

template<typename T, typename U>
inline bool KnowledgeBase<T, U>::function() const
{
	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		return (this->knowledgeVector[i].second.function());
	}
}

template<typename T, typename U>
inline bool KnowledgeBase<T, U>::injection() const
{
	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		return (this->knowledgeVector[i].second.injection());
	}
}

template<typename T, typename U>
inline KnowledgeBase<U, T> KnowledgeBase<T, U>::operator!() const
{
	KnowledgeBase<U, T> result;
	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		BinaryRelation<U, T> tmp = !knowledgeVector[i];
		for (int j = 0; j < tmp.getSize(); j++)
		{
			result.addNewRelation(knowledgeVector[i].getName(), tmp.getPair(j));
		}
	}
	return result;
}

template<typename T, typename U>
inline KnowledgeBase<T, U> KnowledgeBase<T, U>::operator+(const KnowledgeBase& other)
{
	return KnowledgeBase<T, U>(*this) += other;
}

template<typename T, typename U>
inline KnowledgeBase<T, U> KnowledgeBase<T, U>::operator^(const KnowledgeBase<T, U>& other)
{
	return KnowledgeBase<T, U>(*this) ^= other;
}

template<typename T, typename U>
inline KnowledgeBase<T, U>& KnowledgeBase<T, U>::operator+=(const KnowledgeBase<T, U>& other)
{
	for (int i = 0; i < other.knowledgeVector.size(); i++)
	{
		int index = -1; 

		for (int j = 0; j < this->knowledgeVector.size(); j++)
		{
			if (other.knowledgeVector[i].first == this->knowledgeVector[i].first)
			{
				index = j;
				break; 
			}
		}

		if (index != -1)
		{
			this->knowledgeVector[index].second += other.knowledgeVector[i].second;
		}
		else
		{
			addNewRelation(other.knowledgeVector[i].first, other.knowledgeVector[i].second);
		}
	}
	return (*this);
}

template<typename T, typename U>
inline KnowledgeBase<T, U>& KnowledgeBase<T, U>::operator^=(const KnowledgeBase& other)
{
	KnowledgeBase<T, U> result; 

	for (int i = 0; i < this->knowledgeVector.size(); i++)
	{
		for (int j = 0; j < other.knowledgeVector.size(); j++)
		{
			if (this->knowledgeVector[i].first == other.knowledgeVector[j].first)
			{
				BinaryRelation<T, U> temp; 

				temp += this->knowledgeVector[i].second ^ other.knowledgeVector[j].second;
				result.addNewRelation(this->knowledgeVector[i].first, temp);
			}
		}
	}

	this->knowledgeVector = result.knowledgeVector; 

	return (*this);
}
