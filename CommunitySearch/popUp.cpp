#include "popUp.h"

popUp::popUp( Mydatabase& ds, User* user )
{
	setWindowTitle("Cart");

	ds_ = &ds;
	u = user;

	carts = ds_->viewCart(u->getName());


	overallLayout = new QHBoxLayout();
	setLayout(overallLayout);
	Cartlayout = new QVBoxLayout();

	productListWidget = new QListWidget();
	productNameLabel = new QLabel("Products in your cart");
	BuyCart = new QPushButton("Buy Cart");
	Quit = new QPushButton("Close");
	Remove = new QPushButton("Remove Item");

	for (unsigned int i = 0; i < carts.size(); ++i)
	{
		string temp = carts[i]->getName();

		QString str = QString::fromStdString( temp );
		str += "\"\nPrice: ";
		str += QString::fromStdString( std::to_string(carts[i]->getPrice()) );
    	productListWidget->addItem( str );
	}

	Cartlayout->addWidget(productNameLabel);
	Cartlayout->addWidget(productListWidget);
	Cartlayout->addWidget(BuyCart);
	Cartlayout->addWidget(Quit);
	Cartlayout->addWidget(Remove);
	overallLayout->addLayout(Cartlayout);

	connect(BuyCart, SIGNAL(clicked()), this, SLOT(BuyC()));
	connect(Quit, SIGNAL(clicked()), this, SLOT(Q()));
	connect(Remove, SIGNAL(clicked()), this, SLOT(RemoveI()));

}

popUp::~popUp()
{
	
}

void popUp::BuyC()
{
	ds_->buyCart( u->getName() );
	getUser();
}

void popUp::getUser()
{
	carts = ds_->viewCart(u->getName());

	productListWidget->clear();

	for (unsigned int i = 0; i < carts.size(); ++i)
	{
		string temp = carts[i]->getName();

		QString str = QString::fromStdString( temp );
		str += "\"\nPrice: ";
		str += QString::fromStdString( std::to_string(carts[i]->getPrice()) );
    	productListWidget->addItem( str );
	}
}

void popUp::Q()
{
	this->close();
}

void popUp::RemoveI()
{
	int product_index = productListWidget->currentRow();
	if ( product_index < 0)
	{
		return;
	}

	productListWidget->takeItem(product_index);
	carts.erase(carts.begin() + product_index);
}