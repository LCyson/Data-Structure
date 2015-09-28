#include "movie.h"

using namespace std;

Movie::Movie(string Genre , string Rating, const string category, const string name, double price, int qty) : Product(category, name, price, qty) {
	Genre_ = Genre;
	Rating_ = Rating;
}

set<string> Movie::keywords() const
{
	set<string> temp = parseStringToWords(name_);
	set<string> temp2 = parseStringToWords(Genre_);
	set<string> result = setUnion(temp, temp2);
	return result;
}



bool Movie::isMatch(vector<string>& searchTerms) const
{
	set<string> temp = keywords();

	set<string>::iterator it;
	for (it= temp.begin(); it != temp.end(); ++it)
	{
		for (unsigned int i = 0; i < searchTerms.size() ; ++i)
		{
			if ( *it == searchTerms[i] )
			{
				return true;
			}
		}
	}

	return false;
}

string Movie::displayString() const
{
	string result;

	string pricee = to_string(price_);
	string qtyy = to_string(qty_);

	result.append(name_);
	result.append(" \n");
	result.append("Genre: ");
	result.append(Genre_);
	result.append(" Rating: ");
	result.append(Rating_);
	result.append(" \n");
	result.append(pricee);
	result.append(" ");
	result.append(qtyy);
	result.append(" left.");

	return result;
}

void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n";
	os << name_ << "\n";
	os << price_ << "\n";
	os << qty_ << "\n";
	os << Genre_ << "\n";
	os << Rating_ << "\n";
}