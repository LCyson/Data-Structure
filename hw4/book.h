#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include "util.h"

class Book : public Product {
public:
	Book(const std::string, const std::string, const std::string, const std::string, double, int);
	~Book();

	std::set<std::string> keywords() const;
	bool isMatch(std::vector<std::string>& searchTerms) const;
	std::string displayString() const;
	void dump(std::ostream& os) const;

private: 
	std::string ISBN_;	
	std::string Arthor_;

};

#endif