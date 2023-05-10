/* 
	Header:
	Edwin JAsper
	University of Illinois at Chicago
	Program 3: Bar Chart
	Using MacOS and VScode
*/
// bar.h

#include <iostream>
#include <string>
//#include "myrandom.h" // used in graders, do not remove
using namespace std;

//------------------------------
//This is my Bar class that will hold the value of a single bar
class Bar {
 private:
	string name;
	int value; 
	string category; 
 public:
    //----------------------------------
		//This is my default constructor where all values are set to empty, 0.
		Bar() {
			name = "";
			value = 0;
			category = "";
		}

		//--------------------------------------------
		//Paramaterize constructor where private variables are set
    Bar(string name, int value, string category) {
      this->name = name;
			this->value = value;
			this->category = category;
 
    }

    // destructor for my bar class:
    virtual ~Bar() {  
     }

    // getName: will return the name set for the private variable
	string getName() {        
        return name;
	}

    // getValue: will return the value set for the private variable
	int getValue() {
    return value;
	}

    // getCategory: will return the category set for the private varibale
	string getCategory() {
        return category;
	}

	// operators
    // This allows you to compare two Bar
    // objects.  Comparison should be based on the Bar's value.  For example:
	bool operator<(const Bar &other) const {
        return this->value < other.value; 
	}

	bool operator<=(const Bar &other) const {
        return this->value <= other.value; 
	}

	bool operator>(const Bar &other) const {
        return this->value > other.value; 
	}

	bool operator>=(const Bar &other) const {
        return this->value >= other.value; 
	}
};

