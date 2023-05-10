//
//  Project 1 - DNA Profiling
//  Edwin Jasper CS 251 Adam Koehler
//  Using VScode on MacOS
//  no unique function
//

#include "ourvector.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//-----------------------------
//This struct will hold the names and sequence values from the database
struct personDNAInfo{
	string name;
	ourvector<int> numOfSequence;
}; 

//----------------------------------------------------------
//This function reads in the database and stores all the values accordingly
void readInFile(ourvector<ourvector<char>> &sequence, personDNAInfo individual, ourvector<personDNAInfo> &numbers){
	string fileName;
	ifstream file;
	string line;
	string name ="";
	int nucleotideNumber;
	string nucleotideNumber2;
	ourvector<char> nucleotide;
	personDNAInfo temp;

	cin >> fileName;
	file.open(fileName);

	if(!file.is_open()){
		cout << "Error: unable to open " << "'" << fileName << "'" <<endl;
	}
	
	else{
		file >> line;
		for(int i = 5; i < line.size(); i++){
			if (line.at(i) == ','){
				sequence.push_back(nucleotide);
				nucleotide.clear();
			}
			else{
				nucleotide.push_back(line.at(i));
			}
		}
		sequence.push_back(nucleotide);
		file >> line;
		while (!file.fail()){
			size_t found = line.find(',');
			name = line.substr(0,found);
			temp.name = name;
			line.erase(0,found + 1);

			for(int i = 0; i < sequence.size(); i++){
				found = line.find(',');
				nucleotideNumber2 = line.substr(0,found);
				nucleotideNumber = stoi(nucleotideNumber2);
				temp.numOfSequence.push_back(nucleotideNumber) ;
				line.erase(0,found + 1);
			}
			numbers.push_back(temp);
			file >> line;
			temp = {};
		}
		file.close();
	}
}

//----------------------------------------------
//This function stores the dna data into an appropriate char vector
void readInDNA(ourvector<char> &dnaSequence){
	ifstream file;
	string dna;
	string fileName;
	cin >> fileName;
	file.open(fileName);

	if(!file.is_open()){
		cout << "Error: unable to open " << "'" << fileName << "'" << endl;
	}
	file >> dna;
	for(int i = 0; i < dna.size(); i++){
		dnaSequence.push_back(dna.at(i));
	}
}

//------------------------------------------------------------------------------
//This function will compare the long dna info with the individual sequences found in the database
void compareDNASequence(ourvector<int> &numberOfPairs, ourvector<char> dnaSequence, ourvector<ourvector<char>> titleSequence){
	int numberOfSequences = 0;
	int counter = 0;
	int counterForMysteryDNA = 0;
	int sequence = 0;
	int frequency = 0;
	int shizzle = 0;
	
	while(sequence < titleSequence.size()){
		if(shizzle == sequence){
			numberOfPairs.push_back(0);
			shizzle++;
		}
		if(dnaSequence.at(counterForMysteryDNA) == titleSequence.at(sequence).at(counter)){//If the elements are the same
			counter++;
			counterForMysteryDNA++;
			if(counter == titleSequence.at(sequence).size()){
				frequency++;
				counter = 0;
			}
			if(dnaSequence.at(counterForMysteryDNA) != titleSequence.at(sequence).at(counter)){//If next elements aren't equivalent
				counterForMysteryDNA = counterForMysteryDNA - (counter - 1);
				counter = 0;
			if(frequency > numberOfPairs.at(sequence)){
					numberOfPairs.at(sequence) = frequency;
					frequency = 0;
				}
			}
		}
		else{
			counterForMysteryDNA++;
		}
		if(counterForMysteryDNA == dnaSequence.size() - 1){
			sequence++;
			counterForMysteryDNA = 0;
			frequency = 0;
		}
	}
}

//------------------------------------------------------------------------------------
//This function checks to see who the dna sequence belongs to
string searchFunction(ourvector<personDNAInfo> allData, ourvector<int> numberOfPairs){
	int count = 0;
	
	for(int i = 0; i < allData.size(); i++){
		for(int j = 0; j < 3; j++){
			if (allData.at(i).numOfSequence.at(j) == numberOfPairs.at(j)){
				count++;
			}
			if (count == numberOfPairs.size()){
				return allData.at(i).name;
			}
		}
	}
	return "Not found in database.";
}

//----------------------------------------------------------------------------------
//This function checks to see in the database, dna sequence, and process have all been applied
void faultySearch(ourvector<personDNAInfo> allData, ourvector<char> dnaSequence, string process, ourvector<ourvector<char>> dnaProcessing){
	if(allData.size() == 0){
		cout << "No database loaded.\n";
	}
	else if(dnaSequence.size() == 0){
		cout << "No DNA loaded.\n";
	}
	else if(dnaProcessing.size() != 0 || process != ""){
		cout << "No DNA processed.\n";
	}
}

//----------------------------------------------------------------------
//This function checks to make sure the database an dna were already loaded in
void faultyProcess(ourvector<personDNAInfo> allData, ourvector<char> dnaSequence, string &process){
	if(allData.size() == 0){
		cout << "No database loaded.\n";
	}
	else if(dnaSequence.size() == 0){
		cout << "No DNA loaded.\n";
	}
	else{
		cout << "Processing DNA...\n";
		process = "process";
	}
}

//-------------------------------------------------------------
//This function will add a user
void addUserInfo(ourvector<personDNAInfo> &numbers,ourvector<ourvector<char>> &sequence){
	string newUser;
	string nucleotideNumber2;
	int nucleotideNumber;
	string name;
	personDNAInfo temp;
	cout << "Please enter the appropriate amount of numbers and make sure to follow each name and number with a comma and no spaces\n";
	cin.ignore();
	getline(cin,newUser);
	if(numbers.size() == 0){
		cout << "Please input a database first\n";
	}
	else{
		size_t found = newUser.find(',');
		name = newUser.substr(0,found);
		temp.name = name;
		newUser.erase(0,found + 1);
		for(int i = 0; i < sequence.size(); i++){
			found = newUser.find(',');
			nucleotideNumber2 = newUser.substr(0,found);
			nucleotideNumber = stoi(nucleotideNumber2);
			temp.numOfSequence.push_back(nucleotideNumber) ;
			newUser.erase(0,found + 1);
		}
		numbers.push_back(temp);
		temp = {};
	}
}

//--------------------------------------------------
//This function will display the database, dna, process
void display(ourvector<personDNAInfo> allData, ourvector<char> dnaSequence,ourvector<int> numberOfPairs, ourvector<ourvector<char>> dnaProcessing, string process){
	if(allData.size() != 0){
		cout << "Database loaded:\n";
		for(int i = 0; i < allData.size(); i++){
			cout << allData.at(i).name;
			for(int j = 0; j < allData.at(i).numOfSequence.size(); j++){
				cout << " " << allData.at(i).numOfSequence.at(j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	else{
		cout << "No database loaded.\n\n";
	}
	if(dnaSequence.size() != 0){
		cout << "DNA loaded:\n";
		for(int i = 0; i < dnaSequence.size(); i++){
			cout << dnaSequence.at(i);
		}
		cout << endl << endl;
	}
	else{
		cout << "No DNA loaded.\n\n";
	}
	if(dnaProcessing.size() != 0 && process != ""){
		cout << "DNA processed, STR counts:\n";
		for(int i = 0; i < numberOfPairs.size(); i++){
			
			for(int j = 0; j < dnaProcessing.at(i).size(); j++){
				cout << dnaProcessing.at(i).at(j);
			}
			cout << ": " << numberOfPairs.at(i) << endl;
		}
	}
	else{
		cout << "No DNA has been processed.\n";
	}
}

//-----------------------------------------
//This function handles the commands the user enters
void commandOption(){
	ourvector<ourvector<char>> sequence;
	struct personDNAInfo individual;
	ourvector<personDNAInfo> allDNAInfo;
	ourvector<char> dnaSequence;
	ourvector<int> numberOfPairs;
	string command;
	string process = "";
	cout << "Enter command or # to exit: ";
	cin >> command;

	while (command != "#"){
		if(command == "load_db"){
			dnaSequence.clear();
			allDNAInfo.clear();
			sequence.clear();
			cout << "loading database...\n";
			readInFile(sequence,individual, allDNAInfo);
		}
		else if(command == "display"){
			display(allDNAInfo,dnaSequence,numberOfPairs,sequence,process);
		}
		else if(command == "load_dna"){
			cout << "loading DNA...\n";
			readInDNA(dnaSequence);
			compareDNASequence(numberOfPairs, dnaSequence, sequence);
		}
		else if(command == "process"){
			faultyProcess(allDNAInfo, dnaSequence, process);
		}
		else if(command == "search"){
			if(allDNAInfo.size() != 0 && sequence.size() != 0 && process != ""){
				cout << "Searching database...\n";
				if(searchFunction(allDNAInfo, numberOfPairs) != "Not found in database."){
					cout << "Found in database!  DNA matches: " << searchFunction(allDNAInfo, numberOfPairs) << endl;
				}
				else{
					cout << "Not found in database.\n";
				}
			}
			else{
				faultySearch(allDNAInfo,dnaSequence,process,sequence);
			}
		}
		else if(command == "add_new_user"){
			addUserInfo(allDNAInfo, sequence);
		}
		cout << "Enter command or # to exit:";
		cin >> command;
	}
}

int main() {
	string command;
	cout << "Welcome to the DNA Profiling Application.\n";
	commandOption();
	return 0;
}