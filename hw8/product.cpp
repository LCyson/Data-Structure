#include <sstream>
#include <iomanip>
#include "product.h"

using namespace std;


struct InterestingnessComp {
  bool operator()(const Product* lhs, const Product* rhs)
  { 
    return lhs->getInterest() > rhs->getInterest();
  }
};

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

double Product::getInterest()
{
  return Interestingness;
}

double Product::getInterest() const
{
  return Interestingness;
}

void Product::computeInterest( User* u )
{
  Interestingness = 0;
  double R = 0;
  double W = 0;

  std::map<User*, double> Simi = u->getRefinedSim();
  std::vector<Review*> Rev = this->getReview();

  for (std::vector<Review*>::iterator i = Rev.begin(); i != Rev.end(); ++i)
  {
    for (std::map<User*, double>::iterator it = Simi.begin(); it != Simi.end(); ++it)
    {
      if ( it->first->getName() == u->getName() ) return;   
      if ( it->first->getName() == (*i)->getUName() )
      {
        R += (*i)->getRating()*( 1 - it->second);
      }
        W += ( 1 - it->second );
    }
  }

  if ( W == 0 || R == 0 ) return;
  Interestingness = R/W;

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



