#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QImage>
#include <QCoreApplication>
#include <QItemSelectionModel>
#include <QRadioButton>
#include <iomanip>
#include <sstream>
#include <QDialog>
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

#include <string>
#include <vector>

using namespace std;

class popUp : public QDialog
{
	Q_OBJECT
public:
	popUp( Mydatabase& ds, User* user );
	~popUp();

private slots:
	void BuyC();
	void Q();
	void RemoveI();
	void getUser();

private:

	QHBoxLayout* overallLayout;
	QVBoxLayout* Cartlayout;

	// 
	QListWidget* productListWidget;
	QListWidget* usersListWidget;
	QLabel* productNameLabel;
	QLabel* userName;
	QPushButton* BuyCart;
	QPushButton* Quit;
	QPushButton* Remove;



	// Data
	Mydatabase* ds_;
	vector<Product*> carts;
	User* u;

};
