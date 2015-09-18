#include "avltree.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void runCommands(char *file_in, char *file_out, AVLTree<string>& foo)
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
			foo.print(fout);
		}		
		else if (command == "find")
		{
			string item;
			fin >> item;
			if (foo.find(item) == true)
				fout << "find " << item << " true" << endl;
			else
				fout << "find " << item << " false" << endl;
		}
		else if (command == "add")
		{
			string item;			
			fin >> item;
			foo.add(item);
			fout << "add " << item << endl;
		}
		else
		{
			string item;
			fin >> item;
			foo.remove(item);
			fout << "remove " << item << endl;
		}
	}
}

int main(int argc, char* argv[])
{
	AVLTree<string> foo;

	runCommands(argv[1], argv[2], foo);

	return 0;
}
