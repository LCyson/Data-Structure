#include "../alistint.h"
#include <iostream>

using namespace std;

int main() {
  AListInt * alist = new AListInt();

  // Check if the list is initially empty.
  if (alist->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  alist->insert(0, 4);

  // Check if the list is still empty.
  if (!alist->empty()) {
    cout << "SUCCESS: List is not empty after one insertion. Now List has size " << alist->size() << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (alist->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << alist->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (alist->get(0) == 4) {
    cout << "SUCCESS: 4 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 4 is not at the 0th index of the list, " << alist->get(0);
    cout << " is instead." << endl;
  }


  // Insert three items to the list.
  alist->insert(0, 1);
  alist->insert(0, 2);
  alist->insert(0, 3);

  // Insert an items to the second place of the list.
  alist->insert(2, 5);


  // Check if the value and the position are correct.
  if (alist->get(2) == 5) {
    cout << "SUCCESS: 5 is at the 2th index of the list." << endl;
  } else {
    cout << "FAIL: 3.3 is not at the 0th index of the list, " << alist->get(0);
    cout << " is instead." << endl;
  }

  // Insert an items to the last place of the list.
  alist->insert(5, 6);


  // Check if the value and the position are correct.
  if (alist->get(5) == 6) {
    cout << "SUCCESS: 6 is at the 5th index of the list." << endl;
  } else {
    cout << "FAIL: 6 is not at the 5th index of the list, " << alist->get(5);
    cout << " is instead." << endl;
  }


  // Remove an item from the begining of the list.
  alist->remove(0);

  // Check if the value and the position are correct.
  if (alist->get(0) != 3.6) {
    cout << "SUCCESS: 3.6 is removed from the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3.6 is not removed from the list." << endl;
  }

  // Remove an item from the end of the list.
  int posi_4 = alist->get(4);
  alist->remove(4);

  // Check if the value and the position are correct.
  if (alist->get(alist->size()-1) != posi_4) {
    cout << "SUCCESS: 6 is removed from the end of the list." << endl;
  } else {
    cout << "FAIL: 6 is not removed from the list." << endl;
  }

  // Remove an item from the list.
  int posi_2 = alist->get(2);
  alist->remove(2);

  // Check if the value and the position are correct.
  if (alist->get(2) != posi_2) {
    cout << "SUCCESS: 6 is removed from the end of the list." << endl;
  } else {
    cout << "FAIL: 6 is not removed from the list." << endl;
  }

  // Check if the size and returned is correct.
  if (alist->size() == 3) {
    cout << "SUCCESS: Current size is 3." << endl;
  } else {
    cout << "FAIL: Current size isn't 3, it is " << alist->size()<< "instead." << endl;
  }

  //insert 8 numbers into the list
  for (int i = 0; i < 8; ++i)
  {
  	alist->insert(i, i);
  }

  // Check if the size is expanded, if so, check if it is correct.
  if (alist->size() == 11) {
    cout << "SUCCESS: Current size is 11." << endl;
  } else {
    cout << "FAIL: Current size isn't 11, it is " << alist->size()<< "instead." << endl;
  }



  // Clean up memory.
  delete alist;
  return 0;
}