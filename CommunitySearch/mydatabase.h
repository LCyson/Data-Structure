#ifndef MYDATABASE_H
#define MYDATABASE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"
#include "review.h"
#include "spt.h"

/** 
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */
class Mydatabase : public DataStore {
 public:

  Mydatabase();

  ~Mydatabase();

  /**
   * Adds a product to the data store
   */
  void addProduct(Product* p);
 
  /**
   * Adds a user to the data store
   */
  void addUser(User* u);

  std::vector<User*>& getUser();

  std::set<Product*>& getProduct();

  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
  std::vector<Product*> search(std::vector<std::string>& terms, int type);

  /**
   * Reproduce the database file from the current Products and User values
   */
  void dump(std::ostream& ofile);

  void addCart( std::string user_name, Product* product );

  std::vector<Product*> viewCart( std::string user_name );

  void buyCart( std::string user_name );

  void addReview(Review* r);

private:
  SplayTree<std::string, std::set<Product*> > prod;
  std::map<std::string, User*> myuser_;
  std::set<Product*> for_delete;
  std::vector<Review*> for_delete_reviews;
  std::vector<User*> for_delete_u;
  std::map<std::string, std::vector<Product*> > cart;

};

#endif
