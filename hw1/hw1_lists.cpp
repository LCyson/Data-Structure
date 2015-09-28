#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdlib.h>
using namespace std;

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

void readLists(Item*& head1, Item*& head2, const char * argv[]);
void append(Item*& head, int v) ;
void printList(ostream& ofile, Item* head);
Item* concatenate(Item* head1, Item* head2);  
void removeEvens(Item*& head);
double findAverage(Item* head);
double findItems_helper(Item* head, double count);
double findAverage_helper(Item* head);


void readLists(Item*& head1, Item*& head2, const char * name){
    ifstream myfile;
    string line;

    myfile.open(name);
    getline(myfile, line);
    stringstream fil(line);
    int tempVal;

    fil>>tempVal;
    while(fil&&!line.empty()){
      append(head1, tempVal);
      fil>>tempVal;
    }

    getline(myfile, line);
    stringstream fil2(line);
    fil2>>tempVal;    
    while(fil2&&!line.empty()){
      append(head2, tempVal);
      fil2>>tempVal;    
    }

    myfile.close();
}

void append(Item*& head, int v){
  Item* newptr=new Item(v, NULL);
  if(head == NULL){
    head = newptr;
  }
 else {
    Item* temp;
    for(temp = head;temp->next;temp = temp->next);
      temp->next = newptr; 
 }
}

Item* concatenate(Item* head1, Item* head2){
  if(head1 != NULL) {
    return new Item(head1->val, concatenate(head1->next, head2));
  }
  else if (head2 !=NULL){
    return new Item(head2->val, concatenate(head1, head2->next));
  }
  else{
    return NULL;
  }
}

void printList(ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
}

void removeEvens(Item*& head){
  if(head->next==NULL&&head->val%2!=0) return;
  if(head->val%2==0){
      Item* newptr=new Item(0, NULL);
      newptr = head;
      if(head->next) head=head->next;
      else{
	head=NULL;
	return;
      }
      free(newptr);
      removeEvens(head);
    }
  else {
    removeEvens(head->next);
  }
}

double findAverage(Item* head){
  double num=0;
  double count=findItems_helper(head, num);
  return findAverage_helper(head)/findItems_helper(head, count);
}

double findAverage_helper(Item* head){
  if(head==NULL)
    return 0;
  else{
    return findAverage_helper(head->next) + head->val;
  }
}

double findItems_helper(Item* head, double count){
  if(head==NULL) return 0;
  else{
    return findItems_helper(head->next, count)+1;
  }
}



int main(int argc, const char * argv[]) {
  Item* head1=NULL; 
  Item* head2=NULL;
  ofstream ofile;
  ofile.open(argv[2]);
  
  if(!ofile.is_open()){
    cout<<"Please enter the output file's name."<<endl;
    return 0;
  }

  readLists(head1, head2, argv[1]);

  Item* head3 = concatenate(head1, head2);
  printList(ofile, head3);
  removeEvens(head3);
  printList(ofile, head3);
  double ave=findAverage(head3);
  printList(ofile, head3);
  ofile << ave  << " ";
  

  
  return 0;

}

