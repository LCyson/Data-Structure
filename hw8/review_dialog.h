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

class review_Dialog : public QDialog
{
	Q_OBJECT
public:
	review_Dialog( Mydatabase& ds, Product* p );
	~review_Dialog();

private slots:
	void Store();
	void Q();

private:

	QVBoxLayout* overallLayout;
	QVBoxLayout* Cartlayout;
	QHBoxLayout* DateLayout;

	// 
	QListWidget* productListWidget;
	QListWidget* usersListWidget;
	QLineEdit* data_line;
	QLineEdit* rating_line;
	QTextEdit* review_line;
	QLabel* AddReview;
	QLabel* Date;
	QLabel* Rating;
	QPushButton* StoreReview;
	QPushButton* Quit;



	// Data
	Mydatabase* ds_;
	Product* pro;
	string date;
	string rating;
	string review;
};
