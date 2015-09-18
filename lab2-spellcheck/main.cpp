#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

/* Creates dictionary set of words without punctuation and all lowercase from dictionary file */
void getDictionary(char *filename, set<string> &dictionary)
{
	// Open and initialize filestream
	ifstream fin;
	fin.open(filename);

	// Retreive word from file
	string word;
	while (getline(fin, word))
	{	
		// Change word to lowercase
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		// Strip word of punctuation
		string stripWord;
		int n = word.size();
		for (int i = 0; i < n; i++)
			if (!ispunct(word[i]))
				stripWord += word[i];

		// Add word to dictionary
		dictionary.insert(stripWord);
	}
}

/* Create map of mispelled words with line numbers of where in the document they are */
void checkDocument(char *filename, set<string> dictionary, map<string,list<int>> &mispelled)
{
	// Initialize and open filestream
	ifstream fin;
	fin.open(filename);
	
	// Get first line from file
	int lineNumber = 1;
	string inputLine;
	while (getline(fin, inputLine))
	{
		// Set line to lowercase
		transform(inputLine.begin(), inputLine.end(), inputLine.begin(), ::tolower);

		// Strip line of puncuation (split hyphenated words as well)
		string stripLine;
		int n = inputLine.size();
		for (int i = 0; i < n; i++) // Loop through line
			if (!ispunct(inputLine[i]) && !isdigit(inputLine[i]))
				stripLine += inputLine[i]; // If char wasn't puncutation or number, add it
			else
				stripLine += ' '; // If char was punctuation, replace it with space

		// Initialize and open stringstream of the line		
		stringstream ss(stripLine);

		// Get each word from stringstream
		string word;
		while (ss >> word)
		{
			// Check if the word is in the dictionary and add it to mispelled map
			if (dictionary.find(word) == dictionary.end())
			{
				if (mispelled.find(word) == mispelled.end()) // If the word is not in the map, add it
					mispelled.insert(pair<string,list<int>>(word,{lineNumber}));
				else // If the word is already in the map simply add the line number to the list
					mispelled[word].push_back(lineNumber);
			}
		}
		
		// Go to the next line
		lineNumber++;
	}
}

/* Print the mispelled words map to the output file */
void printMispelled(char *filename, map<string,list<int>> &mispelled)
{
	// Open and initialize filestream
	ofstream fout;
	fout.open(filename);
	
	// Iterate through map to print each key and list element
	map<string,list<int>>::iterator iter;
	for (iter = mispelled.begin(); iter != mispelled.end(); iter++)
	{
		fout << iter->first << ":"; // Print the key, (word)
		
		// Iterate through the associated list
		list<int>::iterator listIter;
		for (listIter = iter->second.begin(); listIter != iter->second.end(); listIter++)
			fout << " " << *listIter; // Print each element of the list
		fout << endl;
	}
}

/* A test function that will print the dictionary set */
void printDictionary(set<string> dictionary)
{
	cout << "testing..." << endl;
	set<string>::iterator iter;
	for (iter = dictionary.begin(); iter != dictionary.end(); iter++)
		cout << *iter << endl;
}

int main(int argc, char *argv[])
{
	// Initialize dictionary set and mispelled map
	set<string> dictionary;
	map<string,list<int>> mispelled;

	getDictionary(argv[1], dictionary);

	checkDocument(argv[2], dictionary, mispelled);

	// Test function
	//printDictionary(dictionary);

	printMispelled(argv[3], mispelled);

	return 0;
}
