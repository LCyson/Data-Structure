#include "../llistdbl.h"
#include <iostream>

using namespace std;

int main() {
  LListDbl * list = new LListDbl();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list->insert(0, 3.3);

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion. Now List has size " << list->size() << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3.3) {
    cout << "SUCCESS: 3.3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3.3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }


  // Insert three items to the list.
  list->insert(0, 3.4);
  list->insert(0, 3.5);
  list->insert(0, 3.6);

  // Insert an items to the second place of the list.
  list->insert(2, 5);


  // Check if the value and the position are correct.
  if (list->get(2) == 5) {
    cout << "SUCCESS: 5 is at the 2th index of the list." << endl;
  } else {
    cout << "FAIL: 3.3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Insert an items to the last place of the list.
  list->insert(5, 6);


  // Check if the value and the position are correct.
  if (list->get(5) == 6) {
    cout << "SUCCESS: 6 is at the 5th index of the list." << endl;
  } else {
    cout << "FAIL: 6 is not at the 5th index of the list, " << list->get(5);
    cout << " is instead." << endl;
  }


  // Remove an item from the begining of the list.
  list->remove(0);

  // Check if the value and the position are correct.
  if (list->get(0) != 3.6) {
    cout << "SUCCESS: 3.6 is removed from the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3.6 is not removed from the list." << endl;
  }

  // Remove an item from the end of the list.
  int posi_4 = list->get(4);
  list->remove(4);

  // Check if the value and the position are correct.
  if (list->get(list->size()-1) != posi_4) {
    cout << "SUCCESS: 6 is removed from the end of the list." << endl;
  } else {
    cout << "FAIL: 6 is not removed from the list." << endl;
  }

  // Remove an item from the list.
  int posi_2 = list->get(2);
  list->remove(2);

  // Check if the value and the position are correct.
  if (list->get(2) != posi_2) {
    cout << "SUCCESS: 6 is removed from the end of the list." << endl;
  } else {
    cout << "FAIL: 6 is not removed from the list." << endl;
  }


  // Clean up memory.
  delete list;
  return 0;
}