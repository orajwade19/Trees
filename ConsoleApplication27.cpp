// ConsoleApplication27.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using std::cout;
using std::cin;
class node
{	
private:
	char data;
	node* left;
	node* right;
	friend class tree;
public:
	void set()
	{
		cout << "\nEnter Character Data: ";
		cin >> data;
		left = NULL;
		right = NULL;
	}
	void display()
	{
		cout << data;
	}
};

class tree
{
private:
	node* root;
public:
	tree()
	{
		root = NULL;
	}
	void rCreate()
	{
		char choice;
		root = new node;
		root->set();
		cout << "\nDo you want to keep adding nodes? ";
		cin >> choice;
		while (choice == 'y' || choice=='Y')
		{
			rCreate(root);
			cout << "\nDo you want to keep adding nodes? ";
			cin >> choice;
		}
		
	}
	void rCreate(node* current)
	{
		char choice;
		cout << "\nDo you want to go left or right?";
		cin >> choice;
		if (choice == 'l')
		{
			if (current->left == NULL)
			{
			current->left = new node;
			current->left->set();
			}
			else
			{
				rCreate(current->left);
			}
		}
		else
		{
			if (current->right == NULL)
			{
				current->right= new node;
				current->right->set();
			}
			else
			{
				rCreate(current->right);
			}
		}
	}
	void display()
	{
		display(root);
	}
	void display(node* current)
	{
		current->display();
		if(current->left!=NULL)
			display(current->left);
		if (current->right != NULL)
			display(current->right);
	}
};
int main()
{
	tree k;
	k.rCreate();
	k.display();
    return 0;
}

