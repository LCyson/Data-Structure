#include "book.h"

using namespace std;

Book::Book(const string ISBN , const string Arthor, const string category, const string name, double price, int qty) : Product(category, name, price, qty) {
	ISBN_ = ISBN;
	Arthor_ = Arthor;
}

Book::~Book()
{

}

set<string> Book::keywords() const
{
	set<string> temp = parseStringToWords(name_);
	set<string> temp2 = parseStringToWords(Arthor_);
	temp.insert(ISBN_);
	temp = setUnion(temp, temp2);
	return temp;
}



bool Book::isMatch(vector<string>& searchTerms) const
{
	return false;
}

string Book::displayString() const
{
	string result;

	double priceee = price_;
	string pricee = to_string(priceee);

	string qtyy = to_string(qty_);

	result.append(name_);
	result.append(" \n");
	result.append("Arthor: ");
	result.append(Arthor_);
	result.append(" ISBN: ");
	result.append(ISBN_);
	result.append(" \n");
	result.append(pricee);
	result.append(" ");
	result.append(qtyy);
	result.append(" left. \n");

	return result;
}

void Book::dump(std::ostream& os) const
{
	os << category_ << "\n";
	os << name_ << "\n";
	os << price_ << "\n";
	os << qty_ << "\n";
	os << ISBN_ << "\n";
	os << Arthor_ << "\n";
}