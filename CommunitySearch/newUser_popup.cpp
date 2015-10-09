#include "newUser_popup.h"

NewUser_Popup::NewUser_Popup( Mydatabase& main_ds, vector<User*>& user_v )
{
	ds = &main_ds;
	u = user_v;

	Create_Error = new Error_Popup(2);

	// Title
	setWindowTitle("Log in");

	// Overall layout
	overallLayout = new QVBoxLayout();

	// User's name and password input
	user_name = new QLabel("New account:");
	overallLayout->addWidget(user_name);
	Name = new QLineEdit();
	overallLayout->addWidget(Name);

	user_password = new QLabel("PassWord: (cannot be longer than 8 characters or contain whitespace.)");
	overallLayout->addWidget(user_password);
	Password = new QLineEdit();
	overallLayout->addWidget(Password);

	Age = new QLabel("Age:");
	overallLayout->addWidget(Age);
	UserAge = new QLineEdit();
	overallLayout->addWidget(UserAge);

	Balance = new QLabel("Balance:");
	overallLayout->addWidget(Balance);
	UserBalance = new QLineEdit();
	overallLayout->addWidget(UserBalance);

	// Button
	Create = new QPushButton("Create");
	connect(Create, SIGNAL(clicked()), this, SLOT(NewUser()));
	overallLayout->addWidget(Create);

	Quit = new QPushButton("Quit");
	connect(Quit, SIGNAL(clicked()), this, SLOT(Q()));
	overallLayout->addWidget(Quit);

	// Set overall layout
	setLayout(overallLayout);
}

NewUser_Popup::~NewUser_Popup()
{
	
}

void NewUser_Popup::Q()
{
	this->close();
}

void NewUser_Popup::NewUser()
{
	if( Name->text().isEmpty() || Password->text().isEmpty() || UserBalance->text().isEmpty() || UserAge->text().isEmpty() )
	{
		Error();
		return;
	}	
	string userName = Name->text().toStdString();
	string password = Password->text().toStdString();
	int age = stoi( UserAge->text().toStdString() );
	double balance = stod( UserBalance->text().toStdString() );

	for (unsigned int i = 0; i < u.size(); ++i)
	{
		if ( u[i]->getName() == userName )
		{
			Error();
			return;
		}
	}

	if ( password.size() > 8 )
	{
		Error();
		return;
	}

	for (unsigned int i = 0; i < password.size(); ++i)
	{
		if ( password[i] == ' ' )
		{
			Error();
			return;
		}
	}

	int p = hash_password( password );

	User* newUser = new User( userName, age, balance, 0, p );
	ds->addUser( newUser );

	
	//clear preivous info
	UserAge->setText("");
	Name->setText("");
	Password->setText("");
	UserBalance->setText("");
	Q();
}

void NewUser_Popup::Error()
{
	Create_Error->exec();
}
