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
#include <cstring>
#include "mydatabase.h"
#include "review.h"
#include "user.h"
#include "error_popup.h"

#include <string>
#include <vector>

using namespace std;

class NewUser_Popup : public QDialog
{
	Q_OBJECT
public:
	NewUser_Popup( Mydatabase& main_ds, vector<User*>& user_v );
	~NewUser_Popup();

private slots:
	void NewUser();
	void Error();
	void Q();

private:

	QVBoxLayout* overallLayout;

	// Labels and Lines
	QLabel* user_name;
	QLabel* user_password;
	QLabel* Age;
	QLabel* Balance;
	QLineEdit* Name;
	QLineEdit* Password;
	QLineEdit* UserAge;
	QLineEdit* UserBalance;
	QPushButton* Create;
	QPushButton* Quit;

	// Data
	Mydatabase* ds;
	vector<User*> u;
	Error_Popup* Create_Error;
};
