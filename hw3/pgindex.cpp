#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <ctype.h>
#include "llistint.h"
#include <map>

using namespace std;

bool adjust_words(char* word, char* word_copy, int& flag);

//insert key words and page number into the map
void map_insert(map<string, LListInt> &imap, string& expr, 
  int &page_number)
{
  char buffer[128];
  int flag =0;
  stringstream trans(expr);
  char page[] = "<pagebreak>";


  trans >> buffer;  
  char word_copy[strlen(buffer)];



  while(trans && !expr.empty())
  {
    if (strcmp(buffer, page) == 0)
    {
      page_number ++;
      trans >> buffer;
      continue;
    }
    else{
      bool result = adjust_words(buffer, word_copy, flag);
      if (!result)
      { 
        trans >> buffer;
        continue;
      }  
    }


    LListInt page_list;
    pair<std::map<string,LListInt>::iterator,bool> success;

    page_list.push_back(page_number);
    success = imap.insert(make_pair(word_copy, page_list));

    LListInt temp = imap.find(word_copy)->second;
    if (success.second == false && temp.get(temp.size() -1 ) != page_number)
    {
      temp.push_back(page_number);
      imap[word_copy] = temp;
    }

    trans >> buffer;
  }
}

//
bool adjust_words(char* word, char* word_copy, int& flag)
{
  bool success = true;
  flag = 0;
  memset(word_copy, 0, strlen(word_copy));

  if (strlen(word) < 2)
  { 
    success = false;
    return success;
  }

  for (unsigned int i = 0; i < strlen(word); ++i)
  {
    if (isupper(word[i]))
    {
      word_copy[i] = tolower(word[i]);
    }
    else if (word[i] == '-')
    {
      flag ++;
      return success;
    }
    else if (ispunct(word[i]))
    {
      if (i != 0 && i!= strlen(word)-1)
      {
        success = false;
        return success;
      }
    }
    else
    {
      word_copy[i] = word[i];
    }

  }
  return success;
}





void find_words(map<string, LListInt> &imap, string& expr)
{
  if (imap.find(expr) != imap.end())
  {
      LListInt printout = imap.find(expr)->second;
      for (int i = 0; i < printout.size(); ++i)
      {
        cout<< printout.get(i) << " ";
      }
        cout<< endl;
      return;
  }
  else{
        cout<< "None"<<endl;
  }
}






int main(int argc, char *argv[])
{
  map<string, LListInt> pgindex;
  int page_number = 1;

  ifstream myfile;
  ofstream ofile;
  string line;

  myfile.open(argv[1]);
  ofile.open(argv[2]);

  if(argc <= 3) 
  {
    cerr << "Invalid command format" << endl;
    return -1;
  }

  if(!myfile.is_open() || !ofile.is_open())
  {
    cout<<"Please enter the correct input/output file's name."<<endl;
    return 0;
  }

  while(getline(myfile, line))
  {
    map_insert(pgindex, line, page_number);
  }


  myfile.close();

  for (int i = 0; i < argc - 3; ++i)
  {
    string target_word = argv[i + 3];
    find_words(pgindex, target_word);
  }


  return 0;
  
}
