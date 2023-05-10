/*
Edwin Jasper  Search Engine CS 251
Professor Koehler 
Using MacOS Machine with VScode
*/

#include <iostream>
#include "search.h"
using namespace std;

int main() {
	//Testing Harness 1
	string s= "7heLlo's";
    cout << cleanToken(s) << endl; 
	cout << s;
	cout << endl <<ispunct('a') << endl;
	cout << ispunct('@');

	/*
	// Testing Harness 2
	// set<string> tokens = gatherTokens("EGGS! milk, fish,      @  bread cheese");
	// set<string> token;
	// token.insert("eggs");
	// token.insert("milk");
	// token.insert("fish");
	// token.insert("bread");
	// token.insert("cheese");
	// int i = 0;
	// int j = 0;
	// for (auto& person : token)
    //    {
	// 		j++;
    //      std::cout << person << " " << j;
    //    }
	// cout << endl;
	// for(auto& persons : tokens){
	// 	i++;
	// 	cout << i << "" << persons;
	// } 
	// cout << endl;
	// cout << (tokens.size() == 5) << endl;
	// cout << (tokens == token) << endl;
    */
    /*
	// Testing Harness 3
	// string filename = "cplusplus.txt";
	// map<string,set<string>> index;
	// buildIndex(filename, &index);
	// gatherTokens("hello");

	// Testing Harness 4
	// int i = buildIndex(filename, index);
	// cout << index.size();
	// string sentence= "vector +container -pointer";
	// set<string> results = findQueryMatches(index,sentence);
	// for(auto word:results){
	// 	cout << word << " " << endl;
	// }
	// cout << results.size();
	// cout << i;
    */
    /*
	// Testing Harness 5
	// searchEngine("cplusplus.txt");
    */


    return 0;
}