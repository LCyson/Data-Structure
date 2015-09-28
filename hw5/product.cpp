#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;

Product::Product(const std::string category, const std::string name, double price, int qty) : 
  name_(name),
  price_(price),
  qty_(qty),
  category_(category)
{
  averRating = 0;
}

Product::~Product()
{

}


double Product::getPrice() const
{
  return price_;
}

std::string Product::getName() const
{
  return name_;
}

int Product::getRating() const
{
  return averRating;
}

void Product::calRating()
{

  int cout = 0;
  int sum = 0;

  vector<Review*>::iterator it;
  for ( it = reviews.begin(); it != reviews.end(); ++it)
  {
    sum += (*it)->getRating();
    cout ++;
  }

  if ( cout > 0)
  { 
    averRating = int(sum/cout);
  }
}

void Product::storeReview(Review* r) 
{
  reviews.push_back(r);
}


std::vector<Review*> Product::getReview()
{
  return reviews;
}

std::string Product::getFirstName() const
{
  string name_t = name_;
  string temp;
  stringstream ss(name_t);
  ss >> temp;
  return temp;
}

void Product::subtractQty(int num)
{
  qty_ -= num;
}

int Product::getQty() const
{
  return qty_;
}

/**
 * default implementation...can be overriden in a future
 * assignment
 */ 
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
  if (searchTerms.size() == 0)
  {
    return false;
  }
  return false;
}

void Product::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
}



