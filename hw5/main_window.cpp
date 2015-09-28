#include "main_window.h"

MainWindow::MainWindow()
{
  	parser.addProductParser(new ProductBookParser);
  	parser.addProductParser(new ProductClothingParser);
 	parser.addProductParser(new ProductMovieParser);

 	filename = QCoreApplication::arguments().at(1).toStdString();

  	if( parser.parse(filename, ds) ){
    	cerr << "Error parsing!" << endl;
  	}

  	//get users
	u = ds.getUser();


	// Title
	setWindowTitle("Amazon");

	// Overall layout
	overallLayout = new QHBoxLayout();

	//User widget
	userListWidget = new QListWidget();
	userName = new QLabel("Users");
	for (unsigned int i = 0; i < u.size(); ++i)
	{
		QString str = QString::fromStdString( u[i]->getName() );
		userListWidget->addItem( str );
	}


	//Add user widget
	userDisplayLayout = new QVBoxLayout();
	userDisplayLayout->addWidget(userName);
	userDisplayLayout->addWidget(userListWidget);
	overallLayout->addLayout(userDisplayLayout);

	//product display after search
	productDisplayLayout = new QVBoxLayout();
	productReviewDisplay = new QListWidget();
	ReviewName = new QLabel("Reviews");
	productDisplayLayout->addWidget(ReviewName);
	productDisplayLayout->addWidget(productReviewDisplay);
	overallLayout->addLayout(productDisplayLayout);


	// List of all product
	productListWidget = new QListWidget();
	connect(productListWidget, SIGNAL(currentRowChanged(int)), this, SLOT( displayReviews( )) );
	overallLayout->addWidget(productListWidget);


	// Form to search
	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);


	// Product name label
	productNameLabel = new QLabel("Product's Name:");
	formLayout->addWidget(productNameLabel);

	// search input
	SearchInput = new QLineEdit();
	formLayout->addWidget(SearchInput);


	// Button
	OrSearchButton = new QPushButton("Or Search");
	connect(OrSearchButton, SIGNAL(clicked()), this, SLOT(OrSearch()));
	formLayout->addWidget(OrSearchButton);

	AndSearchButton = new QPushButton("And Search");
	connect(AndSearchButton, SIGNAL(clicked()), this, SLOT(AndSearch()));
	formLayout->addWidget(AndSearchButton);

	RatingSortButton = new QPushButton("Rating Order");
	connect(RatingSortButton, SIGNAL(clicked()), this, SLOT(RatingSort()));
	formLayout->addWidget(RatingSortButton);

	AlphaSortButton = new QPushButton("Alphabetical Order");
	connect(AlphaSortButton, SIGNAL(clicked()), this, SLOT(AlphaSort()));
	formLayout->addWidget(AlphaSortButton);

	AddToCart = new QPushButton("Add-To-Cart");
	connect(AddToCart, SIGNAL(clicked()), this, SLOT(AddCart()));
	userDisplayLayout->addWidget(AddToCart);

	ViewCart = new QPushButton("View Cart");
	connect(ViewCart, SIGNAL(clicked()), this, SLOT(ViewC()));
	userDisplayLayout->addWidget(ViewCart);

	AddReview = new QPushButton("Add Review");
	connect(AddReview, SIGNAL(clicked()), this, SLOT(NewReview()));
	productDisplayLayout->addWidget(AddReview);

	Save = new QPushButton("Save date");
	connect(Save, SIGNAL(clicked()), this, SLOT(SaveData()));
	userDisplayLayout->addWidget(Save);

	Quit = new QPushButton("Quit");
	connect(Quit, SIGNAL(clicked()), this, SLOT(Q()));
	userDisplayLayout->addWidget(Quit);
	// Set overall layout
	setLayout(overallLayout);
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::Q()
{
	QApplication::exit();
}

void MainWindow::SaveData()
{
	string filename = "Newdatabase.txt";
	ofstream ofile(filename.c_str());
	ds.dump(ofile);
	ofile.close();
}	

void MainWindow::AndSearch()
{
	hits.clear();
	// Do nothing if user left at least one input blank
	if(SearchInput->text().isEmpty() )
	{
		return;
	}	

	while ( productListWidget->count() > 0 )
	{
		productListWidget->takeItem(0);	
	}

	string term;
	string temp = SearchInput->text().toStdString();
    stringstream ss(temp);
	vector<string> terms;
	while(ss >> term){
	  term = convToLower(term);
	  terms.push_back(term);
	}
	hits = ds.search(terms, 0);
	
	// Create a new list item with the product's name
	if (hits.size() != 0)
	{
		for (unsigned int i = 0; i < hits.size(); ++i)
		{
			string temp = hits[i]->getName();

			QString str = QString::fromStdString( temp );
			str += "\"\nPrice: ";
			str += QString::fromStdString( std::to_string(hits[i]->getPrice()) );
			str += "\"Quantity: ";
			str += QString::fromStdString( std::to_string(hits[i]->getQty()) );
    		productListWidget->addItem( str );
		}
	}

	// Clear the form inputs and the vector
	SearchInput->setText("");
}

void MainWindow::OrSearch()
{
	hits.clear();
	// Do nothing if user left at least one input blank
	if(SearchInput->text().isEmpty() )
	{
		return;
	}	

	while ( productListWidget->count() > 0 )
	{
		productListWidget->takeItem(0);	
	}

	string term;
	string temp = SearchInput->text().toStdString();
    stringstream ss(temp);
	vector<string> terms;
	while(ss >> term){
	  term = convToLower(term);
	  terms.push_back(term);
	}
	hits = ds.search(terms, 1);

	// Create a new list item with the product's name
	if (hits.size() != 0)
	{
		for (unsigned int i = 0; i < hits.size(); ++i)
		{
			string temp = hits[i]->getName();

			QString str = QString::fromStdString( temp );
			str += "\"\nPrice: ";
			str += QString::fromStdString( std::to_string(hits[i]->getPrice()) );
			str += "\"Quantity: ";
			str += QString::fromStdString( std::to_string(hits[i]->getQty()) );
    		productListWidget->addItem( str );
		}
	}


	// Clear the form inputs and the vector
	SearchInput->setText("");
}

void MainWindow::RatingSort()
{
	if (hits.empty())
	{
		return;
	}

	for (unsigned int i = 0; i < hits.size(); ++i)
	{
		hits[i]->calRating();
	}
	

	productListWidget->clear();
	
	//sort it
	ReviewsRatingComp comp;
	mergeSort(hits, comp);

	if (hits.size() != 0)
	{
		for (unsigned int i = 0; i < hits.size(); ++i)
		{
			string temp = hits[i]->getName();

			QString str = QString::fromStdString( temp );
			str += "\"\nPrice: ";
			str += QString::fromStdString( std::to_string(hits[i]->getPrice()) );
			str += "\"Quantity: ";
			str += QString::fromStdString( std::to_string(hits[i]->getQty()) );
    		productListWidget->addItem( str );
		}
	}	

}

void MainWindow::AlphaSort()
{
	if (hits.empty())
	{
		return;
	}

	while ( productListWidget->count() > 0 )
	{
		productListWidget->takeItem(0);	
	}

	//sort it
	ReviewsAlphaComp comp;
	mergeSort(hits, comp);

	if (hits.size() != 0)
	{
		for (unsigned int i = 0; i < hits.size(); ++i)
		{
			string temp = hits[i]->getName();

			QString str = QString::fromStdString( temp );
			str += "\"\nPrice: ";
			str += QString::fromStdString( std::to_string(hits[i]->getPrice()) );
			str += "\"Quantity: ";
			str += QString::fromStdString( std::to_string(hits[i]->getQty()) );
    		productListWidget->addItem( str );
		}
	}
}


void MainWindow::displayReviews()
{
	productReviewDisplay->clear();

	QString productHit;
	int index = productListWidget->currentRow();
	if (index < 0)
	{
		return;
	}
	vector<Review*> r = hits[index]->getReview();

	//sort it	
	ReviewsDateComp comp;
	mergeSort(r, comp);

	for (unsigned int i = 0; i < r.size(); ++i)
	{
		productHit = QString::fromStdString(r[i]->printReview());
		productReviewDisplay->addItem(productHit);
	}
}


void MainWindow::AddCart()
{
	if ( productListWidget->currentRow() < 0 || userListWidget->currentRow() < 0)
	{
		return;
	}

	int user_index = userListWidget->currentRow();
	int product_index = productListWidget->currentRow();

	ds.addCart( u[user_index]->getName(), hits[product_index] );
}

void MainWindow::ViewC()
{
	int user_index = userListWidget->currentRow();
	if ( user_index < 0 )
	{
		return;
	}

	popUp popUpWindow(ds, u[user_index]);
	popUpWindow.exec();
}

void MainWindow::NewReview()
{
	int product_index = productListWidget->currentRow();
	if ( product_index < 0 )
	{
		return;
	}

	review_Dialog newreview(ds, hits[product_index]);
	newreview.exec();

	displayReviews();
}
