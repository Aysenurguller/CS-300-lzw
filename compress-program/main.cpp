#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "hashtable.cpp"

using namespace std;

 

int main()
{

    ifstream input("compin");
    ofstream out("compout");
	string p = "";
	int pos =0, notFound = -1;
   
    //Initializing HashTable
    HashTable<string,int> dictionary (notFound,4096);

    //Initializing (characters with ascii code 256+ resulting with segmentation fault so hash table initialized with first 256 character)
    for (int i = 0; i<256 ; i++)
	{
		dictionary.insert(string(1,char(i)),pos++);
    }

    
    while(!input.eof()){
		//Read file and create p string with them
        char c;
        input.get(c);
		p+= c;
    }

	//Controllers
	int begin = 0;
	int runner=1;

	while(unsigned(begin + runner) <= p.size()){
		//Write all string item's code that in dictionary


		//If string is at the end of p
		if (unsigned(begin + runner) == p.size())
		{
			out<< dictionary.find(p.substr(begin, runner-1))<<" ";
			runner++;
		}

		//If string is in the dictionary
		else if(dictionary.find(p.substr(begin, runner))>0)
		{
			runner++;
		}

		//If string is not in the dictionat
		else
		{
			//prints value
			out<< dictionary.find(p.substr(begin, runner-1))<<" ";

			//compress string
			dictionary.insert(p.substr(begin,runner),pos++);
			begin += (runner)-1;
			runner =1;
		}
	}
     
    return 0;
}