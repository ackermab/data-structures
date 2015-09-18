#pragma once
#include <iostream>

using namespace std;

template <typename ItemType>

class LinkedList
{
private:
	struct Node {
		ItemType item;
		Node* next = NULL;
		Node* prev = NULL;
	};

	int count;
	Node* head;
	Node* tail;

public:
	LinkedList() : count(0), head(NULL), tail(NULL)
	{

	}

	~LinkedList()
	{
		clear();
	}
	
	Node* getNode(int index)
	{
		Node* n = head;
		for (int i = 0; i < index; i++)
			n = n->next;
		
		return n;
	}

	int size()
	{
		return count;
	}

	ItemType remove(int index)
	{
		if (size() == 1)
		{
			Node* n = head;
			ItemType temp = n->item;
			head = NULL;
			tail = NULL;
			count--;
			delete n;
			return temp;
		}
		else if (index == 0)
		{
			Node* n = head;
			ItemType temp = head->item;
			head = n->next;
			//if (head == NULL)
				//tail == NULL;
			//else
				//head->prev == NULL;
			delete n;
			count--;
			return temp;
		}
		else if (index == (size() - 1))
		{
			Node* n = tail;
			ItemType temp = tail->item;
			tail = n->prev;
			//if (tail == NULL)
				//head == NULL;
			//else
				//tail->next == NULL;
			delete n;
			count--;
			return temp;
		}
		else
		{
			Node* n = getNode(index);
			Node* m = n;
			ItemType temp = n->item;
			n->prev->next = m->next;
			n->next->prev = m->prev;
			delete n;
			count--;
			return temp;
		}
	}

	void insert (int index,const ItemType& item)
	{
		Node* n = new Node();
		n->item = item;

		if (size() == 0)
		{
			head = n;
			tail = n;
			//n->prev = NULL;
			//n->next == NULL;
		}
		else if (index == 0)
		{
			head->prev = n;
			n->next = head;
			head = n;
			//n->prev = NULL;
		}
		else if (index == size())
		{
			tail->next = n;
			n->prev = tail;
			tail = n;
			//n->next = NULL;
		}
		else
		{
			Node* m = getNode(index);
			n->next = m;
			n->prev = m->prev;
			m->prev->next = n;
			m->prev = n;
		}

		count++;
	}

	int find(const ItemType& item)
	{
		int index = -1;

		for (int i = 0; i < size(); i++)
			if (getNode(i)->item == item)
			{
				index = i;
				return index;
			}
		return index;
	}

	void clear()
	{
		while(size() > 0)
		{
			remove(0);
		}
	}	
};
