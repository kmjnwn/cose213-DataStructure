#include "hashmap.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * 2021. 11. 1   Won-Ki Jeong
  *
  */

HashMap<MapElem<std::string, int>> *dict = new HashMap<MapElem<std::string, int>>();

void spellcheck(std::string s)
{
	std::cout << "> " << s;

	if(dict->find(s) != NULL && dict->find(s)->val != 0){
		std::cout << " is in the dictionary" << std::endl;
		return;
	}
	std::cout << " is NOT in the dictionary" << std::endl;
	std::cout << "> " << s << " : ";

	bool check = false, comma_check;
	comma_check = false;
	for(int i=0;i<s.length();i++){
		for(int j='a';j<='z';j++){
			if(s[i] != j){
				//make string candidates
				string st = "";
				for(int l=0;l<i;l++){
					st.push_back(s[l]);
				}
				st.push_back(j);
				for(int l=i+1;l<s.length();l++){
					st.push_back(s[l]);
				}

				//find
				if(dict->find(st) != NULL && dict->find(st)->val != 0){
					if(comma_check)	std::cout << ", ";
					std::cout << dict->find(st)->key;
					check = true;
					comma_check = true;
				}
			}
		}
	}

	if(check == false){
		std::cout << "no suggestion" << std::endl;
	}
	else{
		std::cout << std::endl;
	}

}


int main()
{
	// load dictionary
	char filename[] = "dictionary.txt";
	std::ifstream ifs(filename, std::ifstream::in);
	std::string s((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	std::transform(s.begin(), s.end(),
				   s.begin(), ::tolower);

	std::string token;	
	unsigned int len = s.length();
	
	for(int i=0; i<len; i++)
	{
		int ascii = s[i];
		
		if(ascii < 97 || ascii > 127) 
		{
			if(token.length() > 0) 
			{
				// ToDo
				// Insert token to hash map
				dict->insert(token, 1);
				token.clear();
			}
			continue;
		}
		token.push_back(s[i]);
	}
	
	dict->print();
	std::cout << "mapsize : " << dict->size() << std::endl;
	while(1)
	{
		std::string s;
		std::cout << "insert : ";
		std::cin >> s;
		std::cout << std::endl;

		if(s.compare("q") == 0) break;
		
		dict->insert(s, 1);
	}
	std::cout << "mapsize : " << dict->size() << std::endl;

	while(1)
	{
		std::string s;
		std::cout << "remove : ";
		std::cin >> s;
		std::cout << std::endl;

		if(s.compare("q") == 0) break;
		
		dict->remove(s);
	}

	while(1)
	{
		std::string s;
		std::cout << "find : ";
		std::cin >> s;
		std::cout << std::endl;

		if(s.compare("q") == 0) break;
		
		std::cout << dict->find(s) << std::endl;
	}


	std::cout << "mapsize : " << dict->size() << std::endl;
	
	//
	// infinite loop to accept user input word
	//
	while(1)
	{
		std::string s;
		std::cout << "> ";
		std::cin >> s;
		spellcheck( s );
		
		if(s.compare("q") == 0) break;
	}
	
	
	return 0;
}

/*
//insertion & removing test code

	std::cout << "mapsize : " << dict->size() << std::endl;
	while(1)
	{
		std::string s;
		std::cout << "insert : ";
		std::cin >> s;
		std::cout << std::endl;

		if(s.compare("q") == 0) break;
		
		dict->insert(s, 1);
	}
	std::cout << "mapsize : " << dict->size() << std::endl;

	while(1)
	{
		std::string s;
		std::cout << "remove : ";
		std::cin >> s;
		std::cout << std::endl;

		if(s.compare("q") == 0) break;
		
		dict->remove(s);
	}
	std::cout << "mapsize : " << dict->size() << std::endl;
*/
