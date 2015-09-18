#pragma once
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

template <typename ItemType>

class AVLTree
{
private:
	struct Node
	{
		ItemType item;
		Node* left = NULL;
		Node* right = NULL;
		int height = 0;
	};

	int count;
	Node* root;

public:
	AVLTree() : count(0), root(NULL)
	{}
	~AVLTree()
	{
		clear();
	}

	void clear()
	{
		while (root != NULL)
			remove(root->item);
	}

	int size() const
	{
		return count;
	}

	bool isLeaf(Node* n)
	{
		if ((n->left == NULL) && (n->right == NULL))
			return true;
		else
			return false;
	}

	int height(Node* n)
	{
		if (n == NULL)
			return 0;
		
		if (isLeaf(n) == true)
			return 1;

		int leftHeight = height(n->left);
		int rightHeight = height(n->right);
		
		if (leftHeight > rightHeight)
			return (leftHeight + 1);
		else
			return (rightHeight + 1);
	}

	void add(const ItemType& item)
	{
		add(item, root);
	}

	void add(const ItemType& item, Node*& n)
	{
		if (n == NULL)
		{
			Node* temp = new Node();
			temp->item = item;
			n = temp;
			count++;
		}
		else if (item < n->item)
			add(item, n->left);
		else if (item > n->item)
			add(item, n->right);

		n->height++;
		rebalance(n);
	}
	
	bool find(const ItemType& item)
	{
		return find(item, root);
	}
	
	bool find(const ItemType& item, Node* n)
	{
		if (n == NULL)
			return false;
		else if (item < n->item)
			return find(item, n->left);
		else if (item > n->item)
			return find(item, n->right);
		else
			return true;
	}

	ItemType findMin(Node* n)
	{
		if (n->left == NULL)
			return n->item;
		else
			return findMin(n->left);
	}

	void remove(const ItemType& item)
	{
		remove(item, root);
	}

	void remove(const ItemType& item, Node*& n)
	{
		if (n == NULL)
			return;
		else if (item < n->item)
		{
			remove(item, n->left);
			n->height = height(n);
		}
		else if (item > n->item)
		{
			remove(item, n->right);
			n->height = height(n);
		}
		else if ((n->left == NULL) && (n->right == NULL))
		{
			Node* temp = n;
			n = NULL;
			delete temp;
			count--;
		}
		else if (n->left == NULL)
		{
			Node* temp = n;
			n = temp->right;
			n->height = temp->height;
			delete temp;
			count--;
		}
		else if (n->right == NULL)
		{
			Node* temp = n;
			n = temp->left;
			n->height = temp->height;
			delete temp;
			count--;
		}
		else
		{
			n->item = findMin(n->right);
			remove(n->item, n->right);
			n->height = height(n);
		}
		
		rebalance(n);
	}

	void print(ofstream& fout)
	{
		if (root != NULL)
			print(fout, root);
	}

	void print(ofstream& fout, Node* n)
	{
		queue<Node*> currentLevel, nextLevel;
		int level = 0;
		int onLevel = 0;

		currentLevel.push(root);

		while (!currentLevel.empty())
		{
			onLevel++;
			Node* temp = currentLevel.front();
			currentLevel.pop();

			if ((onLevel % 8) == 1 && level != 0)
				fout << endl << "level " << level << ": " << temp->item << "(" << height(temp) << ")";
			else if ((onLevel % 8) == 1)
				fout << "level " << level << ": " << temp->item << "(" << height(temp) << ")";
			else
				fout << " " << temp->item << "(" << height(temp) << ")";


			if (temp->left)
				nextLevel.push(temp->left);
			if (temp->right)
				nextLevel.push(temp->right);

			if (currentLevel.empty())
			{
				level++;
				onLevel = 0;
				queue<Node*> tempQueue = currentLevel;
				currentLevel = nextLevel;
				nextLevel = tempQueue;
			}
		}

		fout << endl;
	}

	int balance(Node* n)
	{
		if (n == NULL)
			return 0;

		int leftHeight = height(n->left);
		int rightHeight = height(n->right);
		return (rightHeight - leftHeight);
	}

	void rebalance(Node*& n)
	{
		if (balance(n) == 2)
		{
			if (balance(n->right) == -1)
				rotateRight(n->right);
			rotateLeft(n);
		}
		else if (balance(n) == -2)
		{
			if (balance(n->left) == 1)
				rotateLeft(n->left);
			rotateRight(n);
		}
	}

	void rotateRight(Node*& n)
	{
		Node* temp = n->left;
		n->left = temp->right;
		temp->right = n;
		n = temp;
		n->height = height(n);
	}

	void rotateLeft(Node*& n)
	{
		Node* temp = n->right;
		n->right = temp->left;
		temp->left = n;
		n = temp;
		n->height = height(n);
	}
};
