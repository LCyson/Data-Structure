#include "../stackdbl.h"
#include <iostream>

using namespace std;

int main(){
  StackDbl s;

if (s.empty())
{
  cout<<"ahah"<<endl;
}

  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);
  s.push(6);

  while(!s.empty()){
    cout<< s.top()<<endl;
    s.pop();
  }


  return 0;
}