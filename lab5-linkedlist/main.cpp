#include <iostream>
#include <fstream>
#include <string>
#include "linkedlist.h"

using namespace std;

void runCommands(char *file_in, char *file_out, LinkedList<string>& foo)
{
	ifstream fin;
	fin.open(file_in);
	
	ofstream fout;
	fout.open(file_out);

	string command;
	while (fin >> command)
	{
		if (command == "clear")
		{
			foo.clear();
			fout << "clear" << endl;
		}
		else if (command == "print")
		{
			fout << "print" << endl;
			for (int i = 0; i < foo.size(); i++)
				fout << "node " << i << ": " << foo.getNode(i)->item << endl;
		}		
		else if (command == "find")
		{
			string item;
			fin >> item;
			fout << "find " << item << " " << foo.find(item) << endl;
		}
		else if (command == "insert")
		{
			int index;
			fin >> index;
			string item;			
			fin >> item;
			foo.insert(index, item);
			fout << "insert " << index << " " << item << endl;
		}
		else
		{
			int index;
			fin >> index;
			fout << "remove " << index << " " << foo.remove(index) << endl;
		}
	}
}

int main(int argc, char *argv[])
{
	LinkedList<string> foo;

	runCommands(argv[1], argv[2], foo);

	return 0;
}
