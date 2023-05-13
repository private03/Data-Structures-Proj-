//Project 6: File compression
// STARTER CODE: util.h
//
// Edwin K Jasper
// University of Illinois, Chicago
// CS 251, Fall 2022
//

#pragma once
#include <vector>
#include <hash_map>
#include <unordered_map>
#include "hashmap.h"
#include "bitstream.h"
#include <fstream>
#include <queue>

typedef hashmap hashmapF;
typedef unordered_map < int, string > hashmapE;

struct HuffmanNode
{
  int character;
  int count;
  HuffmanNode *zero;
  HuffmanNode *one;
};

struct compare
{
  bool operator () (const HuffmanNode * lhs, const HuffmanNode * rhs)
  {
    return lhs->count > rhs->count;
  }
};

//
// *This method frees the memory allocated for the Huffman tree.
//
void
freeTree (HuffmanNode * node)
{

  if (node == nullptr)
    {
      return;
    }


  freeTree (node->zero);
  freeTree (node->one);


  delete node;

}

//
// *This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
void
buildFrequencyMap (string filename, bool isFile, hashmapF & map)
{

  // TO DO:  Write this function here.
  if (isFile == true)
    {
      ifstream inFS (filename);
      char c;
      while (inFS.get (c))
	{
	  if (map.containsKey (int (c)) == true)
	    {
	      map.put (int (c), map.get (int (c)) + 1);
	    }
	  else
	    {
	      map.put (int (c), 1);
	    }
	}
      map.put (256, 1);
    }
  else
    {
    for (char c:filename)
	{
	  if (map.containsKey (int (c)) == true)
	    {
	      map.put (int (c), map.get (int (c)) + 1);
	    }
	  else
	    {
	      map.put (int (c), 1);
	    }
	}
      map.put (257, 1);
    }
}

//
// *This function builds an encoding tree from the frequency map.
//
HuffmanNode *
buildEncodingTree (hashmapF & map)
{

  priority_queue < HuffmanNode *, vector < HuffmanNode * >, compare > pq;

  // TO DO:  Write this function here.
  // Step 1: Traverse through the frequency map with vector using hashmap.key
  vector < int >allKeys = map.keys ();
  //cout << allKeys.size() << endl;
  //cout << allKeys[0] << " "<< map.get( allKeys[0]) << endl;
  for (int i = 0; i < allKeys.size (); i++)
    {				//   cout << "Beginning of for loop" << endl;
      // Step 2: Convert the index of vector into node 
      HuffmanNode *node = new HuffmanNode ();
      // cout << "before process" << endl;
      node->character = allKeys[i];
      node->count = map.get (allKeys[i]);
      node->zero = nullptr;
      node->one = nullptr;
      // cout << "after process" << endl;  
      // Step 3: "enqueue" or insert the node in to the priority queue.
      pq.push (node);
      // cout << "end of for loop" << endl;  
    }
  // cout << "outside of for loop" << endl;  
  // Step 4:   add the values together to form a new node and link the 
  // Two node to the new nodes. 

  // Step 4.1: Remove the nodes from the queue 
//if the size of the priority_queue == 1 then stop but otherwise perform function
  while (pq.size () != 1)
    {
      HuffmanNode *copyNode = pq.top ();
      pq.pop ();
      HuffmanNode *newRoot = new HuffmanNode ();
      newRoot->character = NOT_A_CHAR;
      newRoot->count = copyNode->count + pq.top ()->count;
      newRoot->zero = copyNode;
      newRoot->one = pq.top ();
      pq.pop ();
      pq.push (newRoot);
    }
// copy the top node and remove then create new node based on the combined value
// add it 
// remove top again and repeat process

  return pq.top ();		// TO DO: update this return
}

//
// *Recursive helper function for building the encoding map.
//
void
_buildEncodingMap (HuffmanNode * node, hashmapE & encodingMap, string str,
		   HuffmanNode * prev)
{

  if (node == nullptr)
    {
      return;
    }

  if (node->character != NOT_A_CHAR)
    {
      encodingMap[node->character] = str;
    }

  prev = node;

  //Step 2: Recursive call to the left or "zero" and append 0(b4 rf)to the string

  _buildEncodingMap (node->zero, encodingMap, str + "0", prev);


  //Step 3: Recursive call to the right or "one" and append 1(b4 rf)to the string
  _buildEncodingMap (node->one, encodingMap, str + "1", prev);

  // TO DO:  Write this function here


}

//
// *This function builds the encoding map from an encoding tree.
//
hashmapE
buildEncodingMap (HuffmanNode * tree)
{
  hashmapE encodingMap;
  string str = "";
  HuffmanNode *prev = nullptr;
  //Step 1: Call recursive function 
  _buildEncodingMap (tree, encodingMap, str, prev);



  // TO DO:  Write this function here.

  return encodingMap;		// TO DO: update this return
}

//
// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string
encode (ifstream & input, hashmapE & encodingMap, ofbitstream & output,
	int &size, bool makeFile)
{
  // Additional info: create a string varible
  string bitString = "";
  char textChar;
  size = 0;

  //Step 1: loop throught the input stream 
  while (input.get (textChar))
    {


      bitString += encodingMap.at (int (textChar));

    }
  bitString += encodingMap.at (256);
  if (makeFile == true)
    {
      for (int i = 0; i < bitString.size (); i++)
	{
	  ++size;
	  if (int (bitString[i]) == 48)
	    {
	      output.writeBit (0);
	    }
	  else
	    {
	      output.writeBit (1);
	    }
	}

    }
  //Step 2: use the encoding map to concentate to the string
  //Step 3: if makefile == true then writebit(int('0'))

  return bitString;		// TO DO: update this return
}

//
// *Recursive helper function to decode the encoding map.
//
void
_decode (HuffmanNode * root, int &index, string bitString,
	 string & decodedString, HuffmanNode * copyRoot)
{
  if (root == nullptr)
    {
      return;
    }




  if (root->character == PSEUDO_EOF)
    {
      return;
    }
  else if (root->character != NOT_A_CHAR)
    {

      decodedString += root->character;
      root = copyRoot;
    }



  index++;

  if (bitString[index] == '0')
    {
      _decode (root->zero, index, bitString, decodedString, copyRoot);
    }
  else
    {
      _decode (root->one, index, bitString, decodedString, copyRoot);
    }

}

//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string
decode (ifbitstream & input, HuffmanNode * encodingTree, ofstream & output)
{
  string bitString = "";
  string decodedString = "";
  int index = -1;
  while (!input.eof ())
    {
      int bit = input.readBit ();

      bitString += to_string (bit);

    }

  HuffmanNode *copyRoot = encodingTree;
  _decode (encodingTree, index, bitString, decodedString, copyRoot);

  for (int q = 0; q < decodedString.size (); q++)
    {
      output.put (decodedString[q]);
    }

  return decodedString;		// TO DO: update this return
}

//
// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string
compress (string filename)
{
  hashmapF frequencyMap;
  HuffmanNode *encodingTree = nullptr;
  hashmapE encodingMap;
  bool isFile = true;
  buildFrequencyMap (filename, isFile, frequencyMap);
  cout << endl;
  cout << "Building frequency map..." << endl;
  //printMap(frequencyMap);
  cout << endl;

  encodingTree = buildEncodingTree (frequencyMap);
  cout << endl;
  cout << "Building encoding tree..." << endl;
  //printTree(encodingTree, "");
  cout << endl;

  encodingMap = buildEncodingMap (encodingTree);
  cout << endl;
  cout << "Building encoding map..." << endl;
  //printMap(encodingMap);
  cout << endl;

  cout << endl;
  cout << "Encoding..." << endl;

  string fn = (isFile) ? filename : ("file_" + filename + ".txt");

  ofbitstream output (filename + ".huf");
  ifstream input (filename);

  stringstream ss;
  // note: << is overloaded for the hashmap class.  super nice!
  ss << frequencyMap;
  output << frequencyMap;	// add the frequency map to the file
  int size = 0;
  string codeStr = encode (input, encodingMap, output, size, true);
  // count bytes in frequency map header
  size = ss.str ().length () + ceil ((double) size / 8);
  cout << "Compressed file size: " << size << endl;
  cout << codeStr << endl;
  cout << endl;
  output.close ();
  freeTree (encodingTree);
  return codeStr;		// TO DO: update this return

}

//
// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function did.
//
string
decompress (string filename)
{
  hashmapF frequencyMap;
  HuffmanNode *encodingTree = nullptr;
  hashmapE encodingMap;
  bool isFile = true;



  cout << endl;
  cout << "Decoding..." << endl;
  size_t pos = filename.find (".huf");

  string filenames = filename.substr (0, pos);
  buildFrequencyMap (filenames, isFile, frequencyMap);
  encodingTree = buildEncodingTree (frequencyMap);
  pos = filenames.find (".");
  string ext = filenames.substr (pos, filenames.length () - pos);
  filenames = filenames.substr (0, pos);
  ifbitstream input (filenames + ext + ".huf");
  ofstream output (filenames + "_unc" + ext);

  hashmapF dump;
  input >> dump;		// get rid of frequency map at top of file

  string decodeStr = decode (input, encodingTree, output);
  cout << decodeStr << endl;
  cout << endl;
  output.close ();
  freeTree (encodingTree);
  return decodeStr;


}
