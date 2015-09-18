#pragma once
#include <iostream>
#include <fstream>
#include "linkedlist.h"

using namespace std;

template <typename ItemType>

class Hash
{
private:
	LinkedList<ItemType>* table;
	int tableSize = 0;
	int count = 0;

public:
	Hash()
	{
		table = new LinkedList<ItemType>[tableSize];
	}
	~Hash()
	{

		delete [] table;
	}
	
	int size()
	{
		return count;
	}
	
	int tableCount()
	{
		return tableSize;
	}

	void clear()
	{
		delete [] table;
		tableSize = 0;
		count = 0;
		table = new LinkedList<ItemType>[tableSize];
	}

	unsigned hashCode(const string& s)
	{
		unsigned hashIndex = 0;
		int n = s.size();

		for (int i = 0; i < n; i++)
		{
			hashIndex = (hashIndex * 31 + s[i]);
		}

		return (hashIndex % tableSize);
	}

	void print(ofstream& fout)
	{
		for (int i = 0; i < tableSize; i++)
		{
			fout << "hash " << i << ":";
			table[i].print(fout, i);
			if (i + 1 < tableSize)
				fout << endl;
		}
		
		if (tableSize != 0)
			fout << endl;
	}
	
	void grow()
	{
		int temp = tableSize;
		tableSize = tableSize * 2 + 1;
		rehash(temp);
	}

	void shrink()
	{
		int temp = tableSize;
		tableSize = tableSize / 2;
		rehash(temp);
	}

	void rehash(int temp)
	{
		LinkedList<ItemType>* newTable = table;
		table = new LinkedList<ItemType>[tableSize];
		count = 0;	
		for (int a = 0; a < tableSize; a++)
			table[a] = LinkedList<ItemType>();
		for (int i = 0; i < temp; i++)
			for (int j = 0; j < newTable[i].size(); j++)
				add(newTable[i].getNode(j)->item);
		delete [] newTable;
	}

	void add(const ItemType& item)
	{
		if (find(item))
			return;
		if (size() == tableCount())
			grow();

		int index = hashCode(item);
		int n = table[index].size();
		table[index].insert(n, item);
		count++;
	}

	void remove(const ItemType& item)
	{
		if (!find(item))
			return;
		
		int index = hashCode(item);

		table[index].remove(table[index].find(item));
		count--;

		if (count <= tableSize / 2)
			shrink();
	}

	bool find(const ItemType& item)
	{
		if (count == 0)
			return false;

		int index = hashCode(item);

		if (table[index].find(item) > -1)
			return true;
		else
			return false;
	}
};
