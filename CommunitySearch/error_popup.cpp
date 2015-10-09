#include "error_popup.h"

Error_Popup::Error_Popup( int type )
{
	setWindowTitle("Error");


	overallLayout = new QVBoxLayout();
	setLayout(overallLayout);

	if ( type == 1 )
	{	
		ErrorMessage = new QLabel("Invalid account or password");
		overallLayout->addWidget(ErrorMessage);
	}
	if ( type == 2 )
	{	
		ErrorMessage = new QLabel("Repetitive account or invalid password");
		overallLayout->addWidget(ErrorMessage);
	}

	// Button
	Close = new QPushButton("Close");
	connect(Close, SIGNAL(clicked()), this, SLOT(Q()));
	overallLayout->addWidget(Close);
}

Error_Popup::~Error_Popup()
{
	
}

void Error_Popup::Q()
{
	this->close();
}
