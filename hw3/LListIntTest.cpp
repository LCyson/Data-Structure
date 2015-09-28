#include "llistint.h"
#include "gtest/gtest.h"

class LListIntTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	LListIntTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LListIntTest() {
			delete list;
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
		list = new LListInt;

		list->push_back(0);
		list->push_back(1);
		list->push_back(2);
		list->push_back(3);
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
	LListInt* list;
};


TEST_F(LListIntTest, PushNominal) {
	for (int i = 0; i < 4; ++i)
	{	
		EXPECT_EQ(list->get(i), i);
	}

	int temp = list->size();
	list->push_back(4);
	EXPECT_EQ(list->size(), temp+1);
}

TEST_F(LListIntTest, CopyOperatorNominal) {
	LListInt* list2 = new LListInt;
	*list2 = *list;

	//push different number to the end of list and list2
	list->push_back(400);
	list2->push_back(500);

	//the numbers in list2 shouldn't influenced by action to list
  	for (int i = 0; i < 4; ++i)
  	{
		EXPECT_EQ(list2->get(i), i);
  	}


	EXPECT_EQ(list2->get(4), 500);

	delete list2;
}

TEST_F(LListIntTest, CopyConstructorNominal) {
	LListInt list3(*list);

	//push different number to the end of list and list2
	list->push_back(400);
	list3.push_back(500);

	//the numbers in list2 shouldn't influenced by action to list
  	for (int i = 0; i < 4; ++i)
  	{
		EXPECT_EQ(list3.get(i), i);
  	}


	EXPECT_EQ(list3.get(4), 500);
}

