#include "llistdbl.h"
#include <cstdlib>
#include <iostream>

LListDbl::LListDbl()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListDbl::insert(int loc, const double& val)
{
  if (loc>size_)
  {
    std::cout<<loc<< "is an unavailable position."<<std::endl;
    return;
  }

  Item *newItem = new Item;
  newItem->val = val;
  newItem->prev = NULL;
  newItem->next = NULL;
  if (loc == 0)  
  {
    if (size_==0)
    {
      head_=newItem;
      tail_=newItem;
    }
    else{
      Item *temp = getNodeAt(loc);
      temp->prev = newItem;
      head_=newItem;
      tail_= getNodeAt(size_-1);
      newItem->next = temp;
    }
  }
  else if (loc == size_)
  {
      Item *temp = getNodeAt(loc-1);
      tail_ = newItem;
      newItem -> prev = temp;
      temp -> next = newItem;
  }
  else{
  Item *temp1 = getNodeAt(loc);
  Item *temp = getNodeAt(loc-1);

  temp-> next = newItem;
  temp1-> prev = newItem;
  newItem->next = temp1; 
  newItem->prev = temp;
  tail_= getNodeAt(size_-1);
  }
  size_++;
}

/**
 * Complete the following function
 */
void LListDbl::remove(int loc)
{
  if (loc >= size_)
  {
    std::cout<<loc<< "is an unavailable position."<<std::endl;
    return;
  }

  if(loc == 0){
    if (size_ == 1)
    {
      head_ = NULL;
      Item *temp = getNodeAt(loc); 
      delete temp;
      size_--;
      return;
    }
    Item *temp = getNodeAt(loc); 
    head_ = getNodeAt(loc+1);
    delete temp;
  }
  else if(loc == size_-1){
    Item *temp_prev = getNodeAt(loc-1); 
    Item *temp = getNodeAt(loc); 
    temp_prev -> next = NULL;
    tail_ = temp_prev;
    delete temp;
  }
  else{
  Item *temp_prev = getNodeAt(loc-1);
  Item *temp_next = getNodeAt(loc+1);
  Item *temp = getNodeAt(loc); 
  temp_prev-> next= temp_next; 
  temp_next -> prev = temp_prev;     
  tail_ = getNodeAt(size_-1);
  delete temp;
  }
  size_--;
}

void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListDbl::Item* LListDbl::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}
