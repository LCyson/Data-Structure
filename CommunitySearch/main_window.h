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
#include "main_info.h"
#include "newUser_popup.h"

#include <string>
#include <vector>

using namespace std;

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow();
	~MainWindow();

private slots:
	void ViewI();
	void Q();
	bool CheckPass();
	void Sign();

private:

	QVBoxLayout* overallLayout;

	// Buttons and LineEdits
	QLabel* User_n;
	QLabel* Pass_w;
	QLineEdit* PassWord;
	QLineEdit* UserName;
	QPushButton* Quit;
	QPushButton* Login;
	QPushButton* Signup;



	// Data
	string filename;
	Mydatabase ds;
	DBParser parser;
	vector<Product*> hits;
	vector<Product*> carts;
	vector<User*> u;
	User* LoginUser;

	//Popup windows
	Main_Info* information;
	NewUser_Popup* NewAccount;
	Error_Popup* Login_Error;
};
