#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "decompose.cpp"

using namespace std;

int main(){

	int position= 0;
	//Initializing code list that will constructed from compose file
	vector<int>compcode;
	string notFound = string(1,'\0');
	//Initializing hashTable
	Hash<int, string> dictionary(notFound,4096);



	for(int i =0; i<256;i++)
	{
		//Insert ascii chars to dictionary 
		dictionary.insert(position++, string(1,char(i)));
	}

	int code;
	ifstream input("compout");
	ofstream output("decompout");


	while(!input.eof())
	{
		//Ýnsert codes to list
		input>>code;
		compcode.push_back(code);
	}


	compcode.pop_back();
	output<<dictionary.find(compcode[0]); //Print first value
	for(int i = 1; i< compcode.size();i++)
	{
		//code is not in list
		if(compcode[i]< position)
		{
			string prev= dictionary.find(compcode[i-1]);
			string curr= dictionary.find(compcode[i]);

			//add code 
			dictionary.insert(position++, prev+curr[0]);
			//print current value
			output <<curr;
		}
		//code is not decompressed
		else
		{
			//find  previous valur
			string prev= dictionary.find(compcode[i-1]);
			//add code
			dictionary.insert(position,prev+prev[0]);
			//prints
			output<<prev+prev[0];
		}
	}



	return 0;
}