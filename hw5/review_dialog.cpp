#include "review_dialog.h"

review_Dialog::review_Dialog( Mydatabase& ds, Product* p )
{
	setWindowTitle("Add Review");

	ds_ = &ds;
	pro = p;


	overallLayout = new QVBoxLayout();
	setLayout(overallLayout);
	Cartlayout = new QVBoxLayout();
	DateLayout = new QHBoxLayout();

	productListWidget = new QListWidget();
	AddReview = new QLabel("Please add review below.");
	Date = new QLabel("Date(YYYY-MM-DD):");
	Rating = new QLabel("Rating(1-5):");
	StoreReview = new QPushButton("Store");
	Quit = new QPushButton("Close");


	data_line = new QLineEdit();
	rating_line = new QLineEdit();
	review_line = new QTextEdit();

	Cartlayout->addWidget(AddReview);
	Cartlayout->addWidget(review_line);
	Cartlayout->addLayout(DateLayout);
	DateLayout->addWidget(Rating);
	DateLayout->addWidget(rating_line);
	DateLayout->addWidget(Date);
	DateLayout->addWidget(data_line);
	Cartlayout->addWidget(StoreReview);
	Cartlayout->addWidget(Quit);
	overallLayout->addLayout(Cartlayout);

	connect(StoreReview, SIGNAL(clicked()), this, SLOT(Store()));
	connect(Quit, SIGNAL(clicked()), this, SLOT(Q()));

}

review_Dialog::~review_Dialog()
{

}

void review_Dialog::Store()
{
	if(review_line->toPlainText().isEmpty() || rating_line->text().isEmpty() || data_line->text().isEmpty())
	{
		return;
	}		

	review = review_line->toPlainText().toStdString();
	rating = rating_line->text().toStdString();
	date = data_line->text().toStdString();
	int rate = stoi(rating);
	string temp = pro->getName();

	Review* newReview = new Review(temp, rate, date, review);
	ds_->addReview(newReview);

	review_line->setPlainText("");
	rating_line->setText("");
	data_line->setText("");
}

void review_Dialog::Q()
{
	this->close();
}
