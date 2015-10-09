#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QImage>
#include <QCoreApplication>
#include <QApplication>
#include <QItemSelectionModel>
#include <QRadioButton>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <sstream>
#include "product.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "book.h"
#include "Clothing.h"
#include "movie.h"
#include "mydatabase.h"
#include "util.h"
#include "review.h"
#include "user.h"
#include "msort.h"
#include "popUp.h"
#include "review_dialog.h"
#include "heap.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

class Main_Info : public QDialog
{
	Q_OBJECT
public:
	Main_Info( Mydatabase& main_ds, vector<User*>& user, User* currUser );
	~Main_Info();

private slots:
	void OrSearch();
	void AndSearch();
	void RatingSort();
	void AlphaSort();
	void displayReviews();
	void AddCart();
	void ViewC();
	void NewReview();
	void Q();
	void SaveData();

private:

	QHBoxLayout* overallLayout;

	// Displayed quote
	QVBoxLayout* userDisplayLayout;
	QVBoxLayout* productDisplayLayout;
	QListWidget* productReviewDisplay;

	// List of quotes
	QListWidget* productListWidget;
	QListWidget* userListWidget;

	// Form for new quote
	QVBoxLayout* formLayout;
	QLabel* productNameLabel;
	QLabel* userName;
	QLabel* productName;
	QLabel* ReviewName;
	QLineEdit* SearchInput;
	QPushButton* AndSearchButton;
	QPushButton* OrSearchButton;
	QPushButton* RatingSortButton;
	QPushButton* AlphaSortButton;
	QPushButton* AddToCart;
	QPushButton* ViewCart;
	QPushButton* AddReview;
	QPushButton* Quit;
	QPushButton* Save;



	// Data
	Mydatabase ds;
	vector<Product*> hits;
	vector<Product*> carts;
	vector<User*> u;
	set<Product*> Inter;
	User* CurrU;
	Product* Reco;
};
