#include "user.h"
using namespace std;


struct UserDistComp {
  bool operator()(const std::pair<User*, double> lhs, const std::pair<User*, double> rhs)
  { 
    return lhs.second > rhs.second;
  }
};

User::User() : name_("unknown"), age_(0), balance_(0.0), type_(1), PassWord(0)
{

}
User::User(std::string name, int age, double balance, int type, int Pass_w) : 
  name_(name), age_(age), balance_(balance), type_(type), PassWord(Pass_w)
{

}

User::~User()
{

}


int User::getAge() const
{
  return age_;
}

std::string User::getName() const
{
  return name_;
}

double User::getBalance() const
{
  return balance_;
}

void User::deductAmount(double amt)
{
  balance_ -= amt;
}

int User::getEncry() const
{
	return PassWord;
}

void User::dump(std::ostream& os)
{
  os << name_ << " " << age_ << " " << balance_ << " " << type_ << endl;
}

void User::storeReview( Review* r )
{
	R.push_back(r);
}

std::vector<Review*> User::getReview()
{
	return R;
}

std::map<User*, double> User::getBaseSim()
{
	return BaseSim;
}

std::map<User*, double> User::getRefinedSim()
{
	return RefinedSim;
}

void User::computeBaseSimi( std::vector<User*>& v )
{
	double sum = 1.0;
	double count = 0.0;

	for (unsigned int i = 0; i < v.size(); ++i)
	{
		User* A_user = v[i];
		std::vector<Review*> A_reviews = A_user->getReview();

		if ( A_user->getName() == name_ )
		{
			continue;
		}

		for (unsigned int j = 0; j < R.size(); ++j)
		{
			for (unsigned int k = 0; k < A_reviews.size(); ++k)
			{
				if ( A_reviews[k]->getProdName() == R[j]->getProdName() )
				{
					count ++;
					double a = R[j]->getRating();
					double b = A_reviews[k]->getRating();
					sum = abs(a-b)/4;
					// std::cout<< A_user->getName() << " and " << name_ << sum << std::endl;
				}
			}
		}	

		if ( count > 0.0 )
		{
			sum = sum/count;
		}
		BaseSim.insert( make_pair(A_user, sum) );
		sum = 1.0;
		count = 0.0;
	}
}

void User::computeRefinedSimi()
{
	UserDistComp comp;
	Heap< pair<User*, double>, UserDistComp > PQ(2, comp);
	// std::map<User*, double> closeList;

	PQ.push( make_pair( this, 0) );

	std::map<User*, double>::iterator it;
	for ( it = BaseSim.begin(); it != BaseSim.end(); ++it)
	{
		if ( it->first != this)
		{
			PQ.push(make_pair(it->first, 100 ));
			RefinedSim.insert( make_pair(it->first, it->second) );
		}
	}

	while ( !PQ.empty() )
	{
		pair<User*, double> min = PQ.top(); 
		// std::cout<< min.second << std::endl;
		PQ.pop();
		
		std::map<User*, double>::iterator i;
		map<User*, double> Vnode = (min.first)->getBaseSim();
		for ( i = Vnode.begin(); i != Vnode.end(); ++i)
		{
			double vDist = (Vnode.find( i->first ))->second;
			double sDist = (BaseSim.find( i->first ))->second;
			double uDist = (BaseSim.find( min.first ))->second;
			// std::cout<< "here" << vDist << " " << sDist << " " << uDist << std::endl;
			if ( vDist + uDist < sDist  )
			{
				RefinedSim.find(i->first)->second = vDist + uDist;
				// std::cout<< "inside" << RefinedSim.find(i->first)->second << std::endl;
			}	
		}		

	}
}