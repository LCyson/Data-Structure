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

	//initiations of Popups
	Login_Error = new Error_Popup(1);
	NewAccount = new NewUser_Popup(ds, u);

	// Title
	setWindowTitle("Log in");

	// Overall layout
	overallLayout = new QVBoxLayout();

	// User's name and password input
	User_n = new QLabel("Account:");
	overallLayout->addWidget(User_n);
	UserName = new QLineEdit();
	overallLayout->addWidget(UserName);

	Pass_w = new QLabel("PassWord:");
	overallLayout->addWidget(Pass_w);
	PassWord = new QLineEdit();
	overallLayout->addWidget(PassWord);


	// Button
	Login = new QPushButton("Log in");
	connect(Login, SIGNAL(clicked()), this, SLOT(ViewI()));
	overallLayout->addWidget(Login);

	Signup = new QPushButton("Sign up");
	connect(Signup, SIGNAL(clicked()), this, SLOT(Sign()));
	overallLayout->addWidget(Signup);

	Quit = new QPushButton("Quit");
	connect(Quit, SIGNAL(clicked()), this, SLOT(Q()));
	overallLayout->addWidget(Quit);
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

void MainWindow::Sign()
{
	NewAccount->exec();
}

void MainWindow::ViewI()
{
	if ( !CheckPass() )
	{
		Login_Error->exec();
		return;
	}
	information = new Main_Info(ds, u, LoginUser);
	information->exec();
}

bool MainWindow::CheckPass()
{
	if( UserName->text().isEmpty() || PassWord->text().isEmpty() )
	{
		return false;
	}	

	string user = UserName->text().toStdString();
	string password = PassWord->text().toStdString();
	LoginUser = NULL;
	u = ds.getUser();

	for (unsigned int i = 0; i < u.size(); ++i)
	{
		// cout << u[i]->getName() << 	" password: " << u[i]->getEncry()<<endl;
		if ( u[i]->getName() == user )
		{
			LoginUser = u[i];
			// cout << login->getName() <<endl;
			break;
		}
	}

	if ( LoginUser )
	{
		int Pass_w = hash_password( password );
		if ( Pass_w == LoginUser->getEncry() )
		{
			return true;
		}
	}

	return false;
}