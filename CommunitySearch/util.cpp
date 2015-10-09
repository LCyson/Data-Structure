#include <iostream>
#include <sstream>
#include <cmath>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

unsigned int hash_password(std::string code)
{
  unsigned long long encrypt_1 = 0;
  unsigned int encrypt_2[4];
  for (int i = 0; i < 4; ++i)
  {
    encrypt_2[i] = 0;
  }

  for (unsigned int i = 0; i < code.size(); ++i)
  {
    encrypt_1 += (unsigned long long)code[i] * (unsigned long long)pow(128, code.size() - 1 - i);
  }
  // std::cout<< encrypt_1 << std::endl;
  encrypt_2[3] = encrypt_1 % 65521; 
  encrypt_1 = encrypt_1 / 65521;

  encrypt_2[2] = encrypt_1 % 65521;
  encrypt_1 = encrypt_1 / 65521;
  // std::cout<< encrypt_1 << std::endl;
  encrypt_2[1] = encrypt_1 % 65521;
  encrypt_1 = encrypt_1 / 65521;
  // std::cout<< encrypt_1 << std::endl;
  encrypt_2[0] = encrypt_1 % 65521;
  
  unsigned int result = ( (45912 * encrypt_2[0] + 35511 * encrypt_2[1] + 65169* encrypt_2[2] + 4625 * encrypt_2[3] ) % 65521 );
  // std::cout << result << std::endl;
  return result;
}


/** Complete the code to convert a string containing a rawWord 
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWord) 
{
	set<string> result;
	stringstream word(rawWord); 
	string buffer;
  	int word_length = 0;
 	unsigned int last_word = 0;
  	bool punct_flag = false;

	word >> buffer;
  buffer = convToLower(buffer);
  	
  	while(word)
  	{
      buffer = convToLower(buffer);
    	if (buffer.size() < 2)
    	{
      	word >> buffer;
      	continue;
    	}

    	for (unsigned int i = 0; i < buffer.size(); ++i)
    	{
      		word_length++;

          if ( ispunct(buffer[i]) && i == 3 && isdigit(buffer[0]) != 0 )
          {
            break;
          }

      		if ( ispunct(buffer[i]) )
      		{
        		if ( word_length-1 >= 2 )
        		{
           			string temp = buffer.substr( i-word_length+1, word_length-1 );
          			result.insert(temp);
        		}
        		word_length = 0;
        		last_word = i+1;
        		punct_flag = true;
      		}
   		}

    	if ( punct_flag && buffer.size() != last_word )
    	{
    	  	string temp = buffer.substr( last_word );
          	result.insert(temp);
    	}
    	else if ( !punct_flag )
    	{
          	result.insert(buffer);
    	}

    	word_length = 0;
    	word >> buffer;
    	punct_flag = false;
  	}	 

  	return result;
}
