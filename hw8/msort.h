#ifndef MSORT_H
#define MSORT_H
#include <string>
#include <iostream>
#include <vector>
#include <cmath>

template <class T, class Comparator>
void Merge (std::vector<T>& a, int l, int r, int m, Comparator comp);
template <class T, class Comparator>
void MergeSort(std::vector<T>& a, int l, int r, Comparator comp);

struct AlphaStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { 
    return lhs > rhs;
  }
};

struct LengthStrComp {
  bool operator()(const std::string& lhs, const std::string& rhs)
  { 
    return lhs.size() < rhs.size();
  }
};

struct PoiLengthStrComp {
  bool operator()(const std::string* lhs, const std::string* rhs)
  { 
    return lhs->size() < rhs->size();
  }
};

struct PoiAlphaStrComp {
  bool operator()(const std::string* lhs, const std::string* rhs)
  { 
    return (*lhs) < (*rhs);
  }
};

struct NumberStrComp {
  bool operator()(const int& lhs, const int& rhs)
  { 
    return lhs < rhs;
  }  
};

struct ReviewsRatingComp {
  bool operator()(const Product* lhs, const Product* rhs)
  { 
    return lhs->getRating() > rhs->getRating();
  }  
};

struct ReviewsAlphaComp {
  bool operator()(const Product* lhs, const Product* rhs)
  { 
    return lhs->getFirstName() < rhs->getFirstName();
  }  
};

struct ReviewsDateComp {
  bool operator()(const Review* lhs, const Review* rhs)
  { 
    std::vector<int> v1 = lhs->getDate();
    std::vector<int> v2 = rhs->getDate(); 

    if ( v1[0] != v2[0] )
    {
      return v1[0] > v2[0];
    }
    if ( v1[1] != v2[1] )
    {
      return v1[1] > v2[1];
    }
      return v1[2] > v2[2];
  }  
};


template <class T, class Comparator>
void mergeSort(std::vector<T>& mylist, Comparator comp)
{
  MergeSort(mylist, 0, mylist.size() - 1, comp );
}

template <class T, class Comparator>
void MergeSort(std::vector<T>& a, int l, int r,  Comparator comp)
{
    if (l<r) { // otherwise, just one element, which is sorted
        int m = floor((l+r)/2);
        MergeSort(a, l, m, comp);
        MergeSort(a, m+1, r, comp);
        Merge(a, l, r, m, comp); // this is a separate function given below
    }
}

template <class T, class Comparator>
void Merge (std::vector<T>& a, int l, int r, int m, Comparator comp)
{
  std::vector<T> temp;
  int low = l, mid = m+1, k = 0;
  while (low <= m || mid <= r)  
       {
         if (low <= m && (mid > r || comp(a[low], a[mid]) ))
            { temp.push_back(a[low]); low ++; k ++; }
         else { temp.push_back(a[mid]); mid ++; k ++; }
       }
  for (k = 0; k < r+1-l; k ++)
    a[k+l] = temp[k]; 
}

#endif