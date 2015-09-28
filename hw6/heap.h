#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <vector>
#include <functional>
#include <iostream>

template <typename T, typename Comparator >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c);

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  void trickleUp(int loc); 

  //print 
  void print();

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  void heapify(int idx);

  /// returns true if the heap is empty
  bool empty() const;

  int size();

 private:
  /// Add whatever helper functions and data members you need below
 	std::vector<T> heap;
 	Comparator comp;
 	int m_ary;

};

// Add implementation of member functions here

template <typename T, typename Comparator>
Heap<T,Comparator>::Heap(int m, Comparator c)
{
	comp = c;
	m_ary = m;
	T _first;
	heap.push_back(_first);
}

template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap()
{

}

template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const
{
	if ( heap.size() < 2 )
	{
		return true;
	}
		return false;
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item)
{
	heap.push_back(item);
	trickleUp(heap.size()-1); 
}


template <typename T, typename Comparator>
void Heap<T,Comparator>::trickleUp(int loc)
{
// could be implemented recursively 
	int parent = (loc + m_ary - 2)/m_ary;
	while(parent >= 1 && comp(heap[loc], heap[parent]) ) 
	{ 
		T temp = heap[loc];
		heap[loc] = heap[parent];
		heap[parent] = temp;

		loc = parent;
    	parent = (loc + m_ary - 2)/m_ary;
  	}
}



// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return heap[1];


}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }

  heap[1] = heap.back();
  heap.pop_back();
  heapify(1);
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::heapify(int idx)
{
	if( idx*m_ary - m_ary + 2 >= heap.size() ) return;
	int smallerChild = m_ary*idx - m_ary + 2; 

	if( smallerChild < heap.size() ){
		int rChild = smallerChild+1; 
		if( comp(heap[rChild], heap[smallerChild]) ) {
			smallerChild = rChild; 
		}
	}
	
	if( !comp(heap[idx], heap[smallerChild]) ) { 
		T temp = heap[idx];
		heap[idx] = heap[smallerChild];
		heap[smallerChild] = temp;

		heapify(smallerChild);
	}
}


template <typename T, typename Comparator>
void Heap<T,Comparator>::print()
{
	for (unsigned int i = 1; i < heap.size(); ++i)
	{
		std::cout<<heap[i]<<std::endl;
	}
}

template <typename T, typename Comparator>
int Heap<T,Comparator>::size()
{
	return heap.size();
}


#endif

