/*
Keegan Miller Program 2 Search Engine CS 251
Professor Koehler 10/2/2022
Using Windows 10 Machine with Replit
*/

#pragma once

#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <iterator>
#include <sstream>
#include <fstream>
using namespace std;


//-------------------------------------------
//This function takes in a string and outputs the string without any punction at the beginning and end of the string
string cleanToken(string s) { 
	string token;
	int position = 0;
	int secondPosition = 0;
	int checkForLetter = 0;
  for(int i = 0; i < s.size(); i++){
		if(!ispunct(s.at(i))){
			position = i;
			break;
		}
	}
	for(int i = s.size() - 1; i > 0; i--){
		if(!ispunct(s.at(i))){
			secondPosition = i;
			break;
		}
	}
	for(int i = 0; i < s.size(); i++){
		if(isalpha(s.at(i))){
			checkForLetter += 1;
		}
	}
	if(checkForLetter != 0){
		s.erase(secondPosition + 1, s.size());
		s.erase(0,position);
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		return s;
	}
	else{
		return "";
	}
}

//----------------------------------------------
//This function gathers all the words that have been cleaned and stores them in a set of strings
set<string> gatherTokens(string text) {
  set<string> tokens;
	string word = "";
	string newWord = "";

	for(int i = 0; i < text.size(); i++){//loops through the provided sentence
		if((text.at(i) == ' ') && (i != 0) || i + 1 == text.size()){//if there is a space or the text is at the last character
			if(i + 1 == text.size()){//adds the last character to the string word
				word += text.at(i);
			}
			newWord = cleanToken(word);
			if(newWord != ""){
				tokens.insert(newWord);
			}
			word = "";
			newWord = "";
		}	
		else{
			word += text.at(i);
		}
	}
  return tokens;
}

//---------------------------------------------------------------------
//This function stores the key words and the urls into a map called Index
int buildIndex(string filename, map<string, set<string>>& index){
	fstream inFS;  
	string file;
	set<string> tokens;
	int count = 0;
	int lineNumber = 0;
	string word = "";
	inFS.open(filename);
	string url = "";
	if(!inFS.is_open()){
		return 0;
	}
	else{
		while(!inFS.eof()){
			getline(inFS, file);
			lineNumber++;
			if(lineNumber % 2 == 1 && file != ""){
				count++;
				url = file;
			}
			else{
				tokens = gatherTokens(file);
				for(auto word:tokens){
					index[word].insert(url);
				}
			}
		}
	return count;
	}
}

//---------------------------------------------------------------------------------
//This function gets user input and looks for which urls that word occurs in
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
  set<string> result;
	set<string> word1;
	set<string> word2;
	int count = 0;
	size_t found;
	vector<string> words;
	string word = "";
	found = sentence.find(" ");

	for(int i = 0; i < sentence.size(); i++){
		if(sentence.at(i) == ' '){
			words.push_back(word);
			word = "";
		}
		else{
			word += sentence.at(i);
		}
	} 
	words.push_back(word);
	word1 = index[cleanToken(words.at(0))];
	for(int i = 0; i < words.size(); i++){
		if(found != string::npos){
			if(i != 0 && words.at(i).at(0) == '+'){
				word2 = index[cleanToken(words.at(i))];
				set_intersection(word1.begin(), word1.end(), word2.begin(), word2.end(), inserter(result, result.begin()));
				word1 = result;
				result.clear();
			}
			else if(i != 0 && words.at(i).at(0) == '-'){
				word2 = index[cleanToken(words.at(i))];
				set_difference(word1.begin(), word1.end(), word2.begin(), word2.end(), inserter(result, result.begin()));
				word1 = result;
				result.clear();
			}
			else if(i != 0 && words.at(i).at(0) != '-' && words.at(i).at(0) != '+'){
				word2 = index[cleanToken(words.at(i))];
				set_union(word1.begin(), word1.end(), word2.begin(), word2.end(), inserter(result, result.begin()));
				word1 = result;
				result.clear();
			}
		}
		else{
			word1 = index[cleanToken(words.at(i))];
		}
	}
  return word1;
}

//-------------------------------------------------
//This function will remove a few stop words
void stopWords(map<string, set<string>>& index){
	index.erase("to");
	index.erase("the");
	index.erase("so");
	index.erase("but");
}

//-------------------------------------------
//This function calls buildIndex and findQueryMatches and displays the output that these fucntions return
void searchEngine(string filename) {
	string sentence;
	string answer;
	map<string,set<string>> index;
	set<string> results;
	int count = buildIndex(filename, index);

	cout << "Would you like to remove filler words?(Enter yes or no)\n";
	cin >> answer;
	if(answer == "yes"){
		stopWords(index);
	}

	cout << "Stand by while building index...\n";
	cout << "Indexed " << count << " pages containing " << index.size() + 1 << " unique terms\n\n";
	cout << "Enter query sentence (press enter to quit):" << endl;
	getline(cin, sentence);
	while(sentence != ""){
		results = findQueryMatches(index,sentence);
		cout << "Found " << results.size() << " matching pages\n"; 
		for(auto word:results){
			cout << word << " " << endl;
		}
		cout << "\nEnter query sentence (press enter to quit):" << endl;
	  getline(cin, sentence);
	}
	cout << "Thank you for searching!";
}




