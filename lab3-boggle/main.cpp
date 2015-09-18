#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

string wordToLower(string &word)
{
	transform(word.begin(), word.end(), word.begin(), ::tolower);

	return word;
}

void getBoard(char *filename, vector<vector<string>> &board)
{
	ifstream fin;
	fin.open(filename);

	string letter;
	vector<string> input;
	while (fin >> letter)
		input.push_back(wordToLower(letter));
	
	int n = sqrt(input.size());
	for (int i = 0; i < n; i++)
	{
		vector<string> row;
		for (int j = 0; j < n; j++)
			row.push_back(input[i*n+j]);
		board.push_back(row);
	}
}

void printBoard(ofstream &fout, vector<vector<string>> &board)
{
	int n = board.size();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			{
				if (j == (n - 1))
					fout << board[i][j] << endl;
				else
					fout << board[i][j] << " ";
			}
}

void getDictionary(char *filename, set<string> &dictionary)
{
	ifstream fin;
	fin.open(filename);

	string word;
	while (fin >> word)
	{
		dictionary.insert(wordToLower(word));
	}
}

void printDictionary(set<string> &dictionary)
{
	set<string>::iterator iter;
	for(iter = dictionary.begin(); iter != dictionary.end(); iter++)
		cout << *iter << endl;
}

bool isOffBoard(int row, int col, int n)
{
	return (row < 0 || col < 0 || row >= n || col >= n);
}

bool isUsed(int row, int col, vector<vector<bool>> &used)
{
	return used[row][col];
}

void printUsedAndBoard(int n, vector<vector<bool>> &used, vector<vector<string>> &board)
{
	for (int a = 0; a < n; a++)
	{
		for (int b = 0; b < n; b++)
			{
				cout << used[a][b] << " ";
			}
		cout << "- ";
		for (int c = 0; c < n; c++)
			{
				cout << board[a][c] << " ";
			}
		cout << endl;
	}
}
bool isFound(string word, set<string> &dictionary, set<string> &foundWords)
{
	if (word.size() > 3 && dictionary.count(word) && !foundWords.count(word))
		return true;
	else
		return false;
}

bool isPrefix(string word, set<string> &dictionary)
{
	set<string>::iterator iter = dictionary.lower_bound(word);
	if(iter == dictionary.end())
		return false;

	string tempString = *iter;
	if (tempString.compare(0, word.length(), word) == 0)
		return true;
	else
		return false;
}

void find(int row, int col, int n, vector<vector<bool>> &used, set<string> &dictionary, vector<vector<string>> &board, string &word, set<string> &foundWords)
{
	if (isOffBoard(row, col, n))
		return;

	if (isUsed(row, col, used))
		return;

	used[row][col] = 1;

	//print used for testing
	//printUsedAndBoard(n, used, board);
	//cout << word << "\t\tSTART" << endl;
	word += board[row][col];
	//cout << word << "\t\tADD LETTER" << endl;
	if (!isPrefix(word, dictionary))
	{
		//cout << word << "\t\tnotPrefix" << endl;
		if (board[row][col].size() == 2)
			word = word.substr(0, word.size()-2);
		else
			word = word.substr(0, word.size()-1);
		//cout << "reduced to: " << word << endl;
		used[row][col] = 0;
		//cout << "--------------" << endl;
		//printUsedAndBoard(n, used, board);
		//cout << "--------------" << endl;
		return;
	}
	//else
		//cout << word << "\t\tisPrefix" << endl;

	if (isFound(word, dictionary, foundWords))
	{
		//cout <<  word << "\t\tFOUND" << endl;
		foundWords.insert(word);
	}

	find(row-1, col-1, n, used, dictionary, board, word, foundWords);
	find(row-1, col  , n, used, dictionary, board, word, foundWords);
	find(row-1, col+1, n, used, dictionary, board, word, foundWords);
	find(row  , col-1, n, used, dictionary, board, word, foundWords);
	find(row  , col+1, n, used, dictionary, board, word, foundWords);
	find(row+1, col-1, n, used, dictionary, board, word, foundWords);
	find(row+1, col  , n, used, dictionary, board, word, foundWords);
	find(row+1, col+1, n, used, dictionary, board, word, foundWords);

	if (board[row][col].size() == 2)
		word = word.substr(0, word.size()-2);
	else
		word = word.substr(0, word.size()-1);
	used[row][col] = 0;
}

void findWord(set<string> dictionary, vector<vector<string>> board, set<string> &foundWords)
{
	int n = board.size();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			string word;
			vector<vector<bool>> used;
			for (int a = 0; a < n; a++)
			{
				vector<bool> row;
				for (int b = 0; b < n; b++)
					row.push_back(0);
				used.push_back(row);
			}

			find(i,j, n, used, dictionary, board, word, foundWords);
		}
}

void printFoundWords(ofstream &fout, set<string> foundWords)
{
	fout << endl;
	set<string>::iterator iter;
	for(iter = foundWords.begin(); iter != foundWords.end(); iter++)
		fout << *iter << endl;
}

int main (int argc, char *argv[])
{
	set<string> dictionary;
	set<string> foundWords;
	vector<vector<string>> board;
	
	ofstream fout;
	fout.open(argv[3]);

	getDictionary(argv[1], dictionary);
	//printDictionary(dictionary);

	getBoard(argv[2], board);
	printBoard(fout, board);

	findWord(dictionary, board, foundWords);
	printFoundWords(fout, foundWords);

	return 0;
}
