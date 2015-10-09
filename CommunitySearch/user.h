#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <functional>
#include "review.h"
#include "heap.h"

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, int Pass_w);
  virtual ~User();

  int getAge() const;
  double getBalance() const;
  int getEncry() const;
  std::string getName() const;
  std::vector<Review*> getReview();
  void storeReview( Review* r );
  void deductAmount(double amt);
  void computeBaseSimi( std::vector<User*>& v );
  void computeRefinedSimi();
  int getSize();
  virtual void dump(std::ostream& os);
  std::map<User*, double> getBaseSim();
  std::map<User*, double> getRefinedSim();

 private:
  std::string name_;
  int age_;
  double balance_;
  int type_;
  int reviewSize;
  int PassWord;
  std::vector<Review*> R;
  std::map<User*, double> BaseSim;
  std::map<User*, double> RefinedSim;
};
#endif
