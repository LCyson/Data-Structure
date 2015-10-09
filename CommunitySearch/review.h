#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include <set>
#include "util.h"

/**
 * Models a review for the product identified by prodName
 */
struct Review
{
public:
  Review() :  prodName(), rating(), date(), reviewText()
  { }
  Review(std::string& prod, 
	 int& rate, 
	 std::string& d, 
	 std::string& review_text, std::string& u) :
    prodName(prod), 
    rating(rate), 
    date(d), 
    reviewText(review_text),
    user(u)
  { }

  std::string getProdName()
  {
    return prodName;
  }

  std::string printReview()
  {
    std::string result = prodName;
    std::string temp = std::to_string(rating);

    result.append(" \n");
    result.append(temp);
    result.append(" ");
    result.append( date );
    result.append(" ");
    result.append( reviewText );
    result.append(" \n");
    return result;
  }

  int getRating()
  {
    return rating;
  }

  std::string getUName()
  {
    return user;
  }

  std::vector<int> getDate() const
  {
    std::string dat = date;
    std::vector<int> v;
    std::string temp1 = dat.substr(0, 4);
    int t1 = std::stoi(temp1);
    int t2;
    int t3;
    std::string temp2 = dat.substr(5, 2);
    std::string temp3 = dat.substr(8, 2);

    if ( temp2[0] == 0)
    {
      t2 = std::stoi(temp2);
    }
    else{
      t2 = std::stoi(temp2);
    }
    if ( temp3[0] == 0)
    {
      t3 = std::stoi(temp3);
    }
    else{
      t3 = std::stoi(temp3);
    }

    v.push_back(t1);
    v.push_back(t2);
    v.push_back(t3);

    return v;
  } 

  std::set<std::string> keywords()
  {
    std::set<std::string> temp = parseStringToWords(prodName);
    return temp;
  }


void dump(std::ostream& os) const
{
  os << prodName << "\n" << rating << " " << date << " " << reviewText << std::endl;
}  
  
private:
  std::string prodName;
  int rating;
  std::string date;
  std::string reviewText;
  std::string user;
};

#endif
