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

#include <string>
#include <vector>

using namespace std;

class Error_Popup : public QDialog
{
	Q_OBJECT
public:
	Error_Popup( int );
	~Error_Popup();

private slots:
	void Q();

private:

	QVBoxLayout* overallLayout;

	// error message
	QLabel* ErrorMessage;
	QPushButton* Close;
};
