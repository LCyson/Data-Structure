#include "mydatabase.h"
#include <iterator>

using namespace std;

Mydatabase::Mydatabase()
{

}

Mydatabase::~Mydatabase()
{
	for (set<Product*>::iterator it = for_delete.begin(); it != for_delete.end(); ++it)
	{
		delete *it;
	}
	for (set<User*>::iterator it = for_delete_u.begin(); it != for_delete_u.end(); ++it)
	{
		delete *it;
	}
}



void Mydatabase::addProduct(Product* p)
{
	set<string> keywords = p->keywords();

	set<string>::iterator it;
	for ( it = keywords.begin(); it != keywords.end(); ++it)
	{
		if ( prod.find(*it) != prod.end() )
		{
			(prod.find(*it)->second).insert(p);
		}
		else {		
			set<Product*> temp;
			temp.insert(p);
			prod.insert(make_pair( *it, temp ));	
		}
	}

	for_delete.insert(p);
}


void Mydatabase::addUser(User* u)
{
	myuser_.insert(make_pair( u->getName(), u ));
	vector<Product*> pro;
	cart.insert(make_pair( u->getName(), pro ));	
	for_delete_u.insert(u);
}

vector<Product*> Mydatabase::search(vector<string>& terms, int type)
{
	vector<Product*> result;
  	set<Product*> mydata_;

	if (type == 0)
	{
		unsigned int size = terms.size();
		while( size > 0)
		{
			if ( prod.find(terms[size-1]) != prod.end() ){
				if (size == terms.size())
				{
					mydata_ = setUnion( mydata_, prod.find(terms[size-1])->second );
				}
				else{
					mydata_ = setIntersection( mydata_, prod.find(terms[size-1])->second );
				}
			}
			size --;
		}


		set<Product*>::iterator it;
		for (it = mydata_.begin(); it != mydata_.end(); ++it)
		{
			result.push_back(*it);
		}		
	}

	if (type == 1)
	{
		for (unsigned int i = 0; i < terms.size() ; ++i)
		{
			if ( prod.find(terms[i]) != prod.end() )
			{
				mydata_ = setUnion( mydata_, prod.find(terms[i])->second );
			}
		}

		set<Product*>::iterator it;
		for (it = mydata_.begin(); it != mydata_.end(); ++it)
		{
			result.push_back(*it);
		}
	}

	return result;
}

void Mydatabase::dump(std::ostream& ofile)
{
	ofile << "<product> \n";

	set<Product*>::iterator it;
	for (it = for_delete.begin(); it != for_delete.end(); ++it)
	{
		(*it)->dump( ofile );
	}

	ofile << "</product> \n";

	ofile << "<users> \n";

	set<User*>::iterator i;
	for (i = for_delete_u.begin(); i != for_delete_u.end(); ++i)
	{
		(*i)->dump( ofile );
	}

	ofile << "</users> \n";
}


void Mydatabase::addCart( string user_name, Product* product )
{
	if ( cart.find( user_name ) != cart.end() )
	{
		(cart.find(user_name)->second).push_back(product);
	}
	else{
		cout << "Please enter correct name." << endl;
	}
}


vector<Product*> Mydatabase::viewCart( string user_name )
{
	vector<Product*> temp;
	if ( cart.find( user_name ) != cart.end() )
	{
		return cart.find( user_name )->second;
	}
	else{
		cout << "Please enter correct name." << endl;
		return temp;
	}
}


void Mydatabase::buyCart( string user_name )
{
	if ( myuser_.find(user_name) != myuser_.end() )
	{
		User* buyer = myuser_.find(user_name)->second;

	if ( cart.find(user_name) != cart.end() )
	{
		vector<Product*>::iterator it;
		
		for ( it = (cart.find(user_name)->second).begin(); it != (cart.find(user_name)->second).end(); ++it)
		{
			if ( (*it)->getPrice() <= buyer->getBalance() && (*it)->getQty() > 0 )
			{
				buyer->deductAmount( (*it)->getPrice() );
				(*it)->subtractQty(1);
				vector<Product*>::iterator it2 = it;
				--it;
				(cart.find(user_name)->second).erase(it2);
			}
		}
	}
	}
}