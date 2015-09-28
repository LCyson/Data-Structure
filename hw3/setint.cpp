#include "setint.h"
#include "llistint.h"
#include <iostream>
#include <cstdlib>

using namespace std;

SetInt::SetInt()
{
	next_loc = 0;
}

SetInt::~SetInt()
{

}

SetInt::SetInt(const SetInt& other)
{
	int i = 0;
	while(i < other.size())
	{
		this->insert(other.list_.get(i));	
		i++;
	}
}

SetInt& SetInt::operator=(const SetInt& other)
{
	if(this == &other) return *this;
 	if(!empty()) this->list_.clear();

	int i = 0;
	while(i < other.size())
	{
		this->insert(other.list_.get(i));	
		i++;
	}

	return *this;
}


int SetInt::size() const
{
	return list_.size();
}

bool SetInt::empty() const
{
	bool result = list_.empty();
	return result;
}

void SetInt::insert(const int& val)
{
	for (int i = 0; i < list_.size(); ++i)
	{
		if (list_.get(i) == val)
		{
			return;
		}
	}

	list_.push_back(val);
}


void SetInt::remove(const int& val)
{
	for (int i = 0; i < list_.size(); ++i)
	{
		if (list_.get(i) == val)
		{
			list_.remove(i);
			return;
		}
	}
}


int const* SetInt::first()
{
	next_loc = 0;
	const int* temp = &list_.get(0);
	next_loc++;
	return temp;
}


int const* SetInt::next()
{
	if (next_loc == list_.size())
	{
		return NULL;
	}

	const int* temp = &list_.get(next_loc);
	next_loc++;
	return temp;
}


SetInt SetInt::setUnion(const SetInt& other) const
{
	SetInt set3;
	SetInt set_temp1 = *this;
	SetInt set_temp2 = other;


	const int* pointer = set_temp1.first();
	const int* pointer2 = set_temp2.first();

	while(pointer)
	{
		set3.insert(*pointer);
		pointer = set_temp1.next();
	}

	while(pointer2)
	{
		set3.insert(*pointer2);
		pointer2 = set_temp2.next();
	}

	return set3;
}



SetInt SetInt::setIntersection(const SetInt& other) const
{
	SetInt set3;
	SetInt set_temp1 = *this;
	SetInt set_temp2 = other;


	const int* pointer = set_temp1.first();
	const int* pointer2 = set_temp2.first();

	while(pointer2)
	{
		pointer = set_temp1.first();

		while(pointer)
		{
			if (*pointer2 == *pointer)
			{
				set3.insert(*pointer);
			}
			pointer = set_temp1.next();
		}

		pointer2 = set_temp2.next();
	}

	return set3;

}

SetInt SetInt::operator&(const SetInt& other) const
{
	SetInt set3;
	SetInt set_temp1 = *this;
	SetInt set_temp2 = other;


	const int* pointer = set_temp1.first();
	const int* pointer2 = set_temp2.first();

	while(pointer)
	{
		set3.insert(*pointer);
		pointer = set_temp1.next();
	}

	while(pointer2)
	{
		set3.insert(*pointer2);
		pointer2 = set_temp2.next();
	}

	return set3;
}

SetInt SetInt::operator|(const SetInt& other) const
{
	SetInt set3;
	SetInt set_temp1 = *this;
	SetInt set_temp2 = other;


	const int* pointer = set_temp1.first();
	const int* pointer2 = set_temp2.first();

	while(pointer2)
	{
		pointer = set_temp1.first();

		while(pointer)
		{
			if (*pointer2 == *pointer)
			{
				set3.insert(*pointer);
			}
			pointer = set_temp1.next();
		}

		pointer2 = set_temp2.next();
	}

	return set3;
}