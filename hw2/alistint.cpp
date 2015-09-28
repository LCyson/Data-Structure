#include "alistint.h"
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>

AListInt::AListInt()//:size_(0), cap_(10)
{
  size_ = 0;
  cap_ = 10;
  data = new int[cap_];
}

AListInt::AListInt(int cap)
{
  cap_ = cap;
  data = new int[cap_];
}

AListInt::~AListInt()
{
  delete []data;
}

bool AListInt::empty() const
{
  return size_ == 0;
}

int AListInt::size() const
{
  return size_;
}

void AListInt::insert(int pos, const int& val)
{
  if (size_ >= cap_)
  {
    resize();
  }

  if(size_<cap_ && pos>=0 && pos<=size_){
    for(int i=size_; i>pos; i--){
      data[i]=data[i-1];
    }
    data[pos] = val;
  }
  else{
    std::cout<<"position isn't valid"<<std::endl;
  }
  size_++;
}

void AListInt::remove(int pos)
{
  if(pos>=0 && pos<size_){
    for(int i=pos+1; i<size_; i++){
      data[i-1] = data[i];
    }
    size_--;
  }
}

void AListInt::set (int position, const int& val)
{
  data[position] = val;
}


int& AListInt::get (int position)
{
  return data[position];
}

int const & AListInt::get (int position) const
{
  return data[position];
}

void AListInt::resize()
{
  int newlength = 2 * size_;
  cap_ = newlength;
  int *newArray = new int[newlength];

  memcpy(newArray, data, size_ * 4);
  delete[] data;
  data = newArray;
}



