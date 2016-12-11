#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <istream>

#include <stdlib.h> 
using namespace std;


typedef map< vector<string>, vector<string> > myMap;

void addText(myMap& database, string text){
	string w1 = "";
	string w2 = "";
	string w3 = "";
	vector<string> key;
	for (short i = 0; i<text.length(); i++){
	    if (text[i] == ' '){
	    	if(w1 != ""){
	    		key.push_back(w1);
	    		key.push_back(w2);
	    		database[key].push_back(w3);
	    		key.clear();
	    	}
			w1 = w2;
			w2 = w3;
			w3 = "";
	    }
	    else{
	        w3 += text[i];
	    }
	}
	key.clear();
	key.push_back(w1);
	key.push_back(w2);
	database[key].push_back(w3);
}

string generateText(myMap& database){
	vector< vector<string> > starts;
	string genText = "";
	
	myMap::iterator pos;
	for (pos = database.begin(); pos != database.end(); ++pos) {
		char la = pos->first[0][pos->first[0].size()-1];
        if(isupper(pos->first[0][0]) and la != '.' and la != '?' and la != '!'){
        //	cout << pos->first[0] << endl;
        	starts.push_back(pos->first);
        }
       	
	}
	
	srand(time(NULL));
	int v1 = rand() % starts.size();
	vector<string> curKey = starts[v1];
	string w1 = curKey[0];
	string w2 = curKey[1];
	string w3 = "";

	genText += w1 + " " + w2;
	char last = genText[genText.size()-1];

	while(last != '.' and last != '?' and last != '!' and database.count(curKey) > 0){
		int v2 = rand() % database.at(curKey).size();
		w3 = database.at(curKey)[v2];
		genText += " " + w3;
		last = genText[genText.size()-1];
		w1 = w2;
		w2 = w3;
		curKey.clear();
		curKey.push_back(w1);
		curKey.push_back(w2);
	
	}
	//cout << genText << endl;
	return genText;
}

int main(int argc, char** argv)
{
    if(argc != 2){
    	cout << "Incorrect usgae. Must provide exactly 2 arguments." << endl;
    	return 0;
    }
    myMap database;
	
	string str2;
	string str3 = "";
	ifstream myfile (argv[1]);
	if(myfile.is_open()){
		while(getline(myfile, str2)){
			str3 += str2 + " ";
		}
	}
	else{
		cout << "Unable to open the file." << endl;
	}

	addText(database, str3);	
	
	string tweet;
	do{
		tweet = generateText(database);
	}while(tweet.size() > 145 or tweet.size() < 80);
	cout << tweet << endl;
	
	return 0;

}