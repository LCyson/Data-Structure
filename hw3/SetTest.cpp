#include "setint.h"
#include "gtest/gtest.h"

class SetTest : public testing::Test {
protected:
  // You can remove any or all of the following functions if its body is empty.

  SetTest() {
    // You can do set-up work for each test here.
  }

  virtual ~SetTest() {
      
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:
  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).

    set.insert(0);
    set.insert(1);
    set.insert(2);
    set.insert(3);
    set.insert(3);
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }

  // Objects declared here can be used by all tests in the test case.
  SetInt set;
};


TEST_F(SetTest, insertNominal) {
  const int* pointer = set.first();
  int i =0;

  while(pointer)
  {
    EXPECT_EQ(*pointer, i);
    pointer = set.next();    
    i++;
  }
  
//test size
  EXPECT_EQ(set.size(), 4);

  int temp = set.size();
  set.insert(4);
  EXPECT_EQ(set.size(), temp+1);
}

TEST_F(SetTest, removeNominal) {
//remove the first item
      set.remove(0);
      const int* pointer = set.first();

      EXPECT_EQ(*pointer, 1);
      EXPECT_EQ(set.size(), 3);

//remove the last item
      set.remove(3);
      pointer = set.first();
      for (int i = 0; i < set.size() -1; ++i)
      {
        pointer = set.next();
      }
      EXPECT_EQ(*pointer, 2);
      EXPECT_EQ(set.size(), 2);

//remove a random item
      set.insert(5);
      set.insert(6);
      set.remove(5);

      pointer = set.first();
      for (int i = 0; i < set.size() -1; ++i)
      {
        pointer = set.next();
      }
      EXPECT_EQ(*pointer, 6);
      EXPECT_EQ(set.size(), 3);
}

TEST_F(SetTest, setUnionNominal) {
      SetInt s1;
      SetInt s2;
      SetInt s3;
      const int* pointer3 = s3.first();

      s1.insert(1);
      s1.insert(2);
      s1.insert(3);

//when one set is an empty set
      s3 = s1.setUnion(s2);
      pointer3 = s3.first();

      for (int i = 0; i < s3.size(); ++i)
      {
        EXPECT_EQ(*pointer3, i+1);
        pointer3 = s3.next();
      }


//when both set have elements
      s2.insert(2);
      s2.insert(3);
      s2.insert(4);
      s3 = s1.setUnion(s2);
      pointer3 = s3.first();

      for (int i = 0; i < s3.size(); ++i)
      {
        EXPECT_EQ(*pointer3, i+1);
        pointer3 = s3.next();
      }
}

TEST_F(SetTest, setIntersectionNominal) {
      SetInt s1;
      SetInt s2;
      SetInt s3;
      const int* pointer3 = s3.first();

      s1.insert(1);
      s1.insert(2);
      s1.insert(3);

//when one set is an empty set
      s3 = s1.setIntersection(s2);
      pointer3 = s3.first();

      for (int i = 0; i < s3.size(); ++i)
      {
        EXPECT_EQ(*pointer3, i+1);
        pointer3 = s3.next();
      }


//when both set have elements
      s2.insert(2);
      s2.insert(3);
      s2.insert(4);
      s3 = s1.setIntersection(s2);
      pointer3 = s3.first();

      for (int i = 0; i < s3.size(); ++i)
      {
        EXPECT_EQ(*pointer3, i+2);
        pointer3 = s3.next();
      }
}

TEST_F(SetTest, setIntersection_Operator_Nominal) {
      SetInt s1;
      SetInt s2;
      SetInt s3;
      const int* pointer3 = s3.first();

      s1.insert(1);
      s1.insert(2);
      s1.insert(3);

//when one set is an empty set
      s3 = s1|s2;
      pointer3 = s3.first();

      for (int i = 0; i < s3.size(); ++i)
      {
        EXPECT_EQ(*pointer3, i+1);
        pointer3 = s3.next();
      }


//when both set have elements
      s2.insert(2);
      s2.insert(3);
      s2.insert(4);
      s3 = s1|s2;
      pointer3 = s3.first();

      for (int i = 0; i < s3.size(); ++i)
      {
        EXPECT_EQ(*pointer3, i+2);
        pointer3 = s3.next();
      }
}

TEST_F(SetTest, setUnion_Operator_Nominal) {
      SetInt s1;
      SetInt s2;
      SetInt s3;
      const int* pointer3 = s3.first();

      s1.insert(1);
      s1.insert(2);
      s1.insert(3);

//when one set is an empty set
      s3 = s1 & s2;
      pointer3 = s3.first();

      for (int i = 0; i < s3.size(); ++i)
      {
        EXPECT_EQ(*pointer3, i+1);
        pointer3 = s3.next();
      }


//when both set have elements
      s2.insert(2);
      s2.insert(3);
      s2.insert(4);
      s3 = s1 & s2;
      pointer3 = s3.first();

      for (int i = 0; i < s3.size(); ++i)
      {
        EXPECT_EQ(*pointer3, i+1);
        pointer3 = s3.next();
      }
}