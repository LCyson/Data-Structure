#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "book.h"
#include "Clothing.h"
#include "movie.h"
#include "mydatabase.h"
#include "util.h"
/** Add other #includes here **/

using namespace std;

/* Prototypes */
void displayProducts(vector<Product*>& hits, int type);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please specify a database file" << endl;
  }

  /****************
   * Declare your derived DataStore object here replacing
   *  DataStore type to your derived type
   ****************/
  Mydatabase ds;


  // Instantiate the parser
  DBParser parser;

  // Instantiate the individual product parsers we want
  parser.addProductParser(new ProductBookParser);
  parser.addProductParser(new ProductClothingParser);
  parser.addProductParser(new ProductMovieParser);

  // Now parse the database to populate the DataStore
  if( parser.parse(argv[1], ds) ){
    cerr << "Error parsing!" << endl;
    return 1;
  }

  cout << "=====================================" << endl;
  cout << "Menu: " << endl;
  cout << "  AND term term ...                  " << endl;
  cout << "  OR term term ...                   " << endl;
  cout << "  ADD username search_hit_number     " << endl;
  cout << "  VIEWCART username                  " << endl;
  cout << "  BUYCART username                   " << endl;
  cout << "  QUIT new_db_filename               " << endl;
  cout << "====================================" << endl;

  vector<Product*> hits;
  vector<Product*> carts;
  bool done = false;
  while(!done){
    cout << "\nEnter search terms: " << endl;
    string line;
    getline(cin,line);
    stringstream ss(line);
    string cmd;
    if((ss >> cmd)){
      if( cmd == "AND"){
	string term;
	vector<string> terms;
	while(ss >> term){
	  term = convToLower(term);
	  terms.push_back(term);
	}
	hits = ds.search(terms, 0);
	displayProducts(hits, 0);
      }
      else if ( cmd == "OR" ){
	string term;
	vector<string> terms;
	while(ss >> term){
	  term = convToLower(term);
	  terms.push_back(term);
	}
	hits = ds.search(terms, 1);
	displayProducts(hits, 0);
      }
      else if ( cmd == "QUIT"){
	string filename;
	if(ss >> filename){
	  ofstream ofile(filename.c_str());
	  ds.dump(ofile);
	  ofile.close();
	}
	done = true;
      }
      
      else if ( cmd == "ADD" ){
  string term;
  vector<string> terms;
  while(ss >> term){
    term = convToLower(term);
    terms.push_back(term);
  }
  if (!hits.empty() && terms.size() > 1){
    stringstream num;
    unsigned int num_;
    num << terms[1];
    if ( num >> num_ && num_ > 0 && num_ <= hits.size() ){
    ds.addCart( terms[0], hits[num_-1]);
    cout<< hits[num_-1]->getName()<< " is in your cart now. " <<endl;
    }
    else{
      cout<< "NO such thing! Plz enter the right hits' number!" << endl;
    }
  }
      }

      else if ( cmd == "VIEWCART" ){
  string term;
  vector<string> terms;
  while(ss >> term){
    term = convToLower(term);
    terms.push_back(term);
  }
  if ( terms.size() > 0)
  {
  carts = ds.viewCart( terms[0] );
  displayProducts(carts, 1);  }
  }

       else if ( cmd == "BUYCART" ){
  string term;
  vector<string> terms;
  while(ss >> term){
    term = convToLower(term);
    terms.push_back(term);
  }
  if ( terms.size() > 0 )
  {
    ds.buyCart( terms[0] );  
  }
  } 
      /** ADD support for other command here **/


      else {
	cout << "Unknown command" << endl;
      }
    }
    
  }
  return 0;
}
 
void displayProducts(vector<Product*>& hits, int type)
{
  if ( type == 0)
  {
    int resultNo = 1;
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it){
      cout << "Hit " << setw(3) << resultNo << endl;
      cout << (*it)->displayString() << endl;
      cout << endl;
      resultNo++;
    }
  }
  else if ( type == 1 )
  {
    int resultNo = 1;
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it){
      cout << "Item " << setw(3) << resultNo << endl;
      cout << (*it)->displayString() << endl;
      cout << endl;
      resultNo++;
    }
  }

}
