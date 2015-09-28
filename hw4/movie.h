#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "util.h"

class Movie : public Product {
public:
	Movie(std::string, std::string, std::string, std::string, double, int);

	std::set<std::string> keywords() const;
	bool isMatch(std::vector<std::string>& searchTerms) const;
	std::string displayString() const;
	void dump(std::ostream& os) const;

private: 
	std::string Genre_;	
	std::string Rating_;

};

#endif