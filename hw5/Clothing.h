#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include "util.h"

class Clothing : public Product {
public:
	Clothing(std::string, std::string, std::string, std::string, double, int);

	std::set<std::string> keywords() const;
	bool isMatch(std::vector<std::string>& searchTerms) const;
	std::string displayString() const;
	void dump(std::ostream& os) const;

private: 
	std::string Size_;	
	std::string Brand_;

};

#endif