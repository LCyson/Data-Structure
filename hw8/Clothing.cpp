#include "Clothing.h"

using namespace std;

Clothing::Clothing(string Sizee , string Brand, const string category, const string name, double price, int qty) : Product(category, name, price, qty) {
	Size_ = Sizee;
	Brand_ = Brand;
}

set<string> Clothing::keywords() const
{
	set<string> temp = parseStringToWords(name_);
	set<string> temp2 = parseStringToWords(Brand_);
	set<string> result = setUnion(temp, temp2);
	return result;
}



bool Clothing::isMatch(vector<string>& searchTerms) const
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

string Clothing::displayString() const
{
	string result;

	string pricee = to_string(price_);
	string qtyy = to_string(qty_);

	result.append(name_);
	result.append(" \n");
	result.append("Brand: ");
	result.append(Brand_);
	result.append(" Size: ");
	result.append(Size_);
	result.append(" \n");
	result.append(pricee);
	result.append(" ");
	result.append(qtyy);
	result.append(" left.");

	return result;
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n";
	os << name_ << "\n";
	os << price_ << "\n";
	os << qty_ << "\n";
	os << Size_ << "\n";
	os << Brand_ << "\n";
}