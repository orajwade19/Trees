/*
 * Bin.cpp
 *
 *  Created on: 15-Jan-2018
 *      Author: student
 */
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
class Node {
	Node*left, *right;
	char data[15];
public:
	Node() {
		left = NULL;
		right = NULL;
	}
	friend class Bin;
	friend class Sta;
};
class Sta {
	Node*arr[16];
	int top;
	friend class Bin;
public:
	Sta() {
		top = -1;
	}
	void push(Node*);
	Node* pop();
	bool isempty();
};
bool Sta::isempty() {
	if (top == -1)
		return 1;
	else
		return 0;
}
void Sta::push(Node*t) {
	arr[++top] = t;
}
Node* Sta::pop() {
	if (!isempty()) {
		return arr[top--];
	} else
		return NULL;
}
class Bin {
	Node*root;
public:
	Bin() {
		root = NULL;
	}
	void create();
	void rcreate();
	void rcreate(Node*, int);
	void rdisplayin(Node*);
	void rdisplaypre(Node*);
	void rdisplaypost(Node*);
	void display();
	void displayin(Node*);
	void displaypre(Node*);
	void displaypost(Node*);
	Node* rcopy(Node*);
	void operator =(Bin);
	Bin copy();
	void remove();
};
void Bin::displayin(Node*p) {
	Node*temp = p;
	Sta r;
	while (1) {
		while (temp != NULL) {
			r.push(temp);
			temp = temp->left;
		}
		if (r.top == -1)
			break;
		temp = r.pop();
		cout << temp->data<<"\t";
	}
}
void Bin::displaypre(Node*p) {
	Node*temp = p;
	Sta r;
	while (1) {
		while (temp != NULL) {
			cout << temp->data<<"\t";
			r.push(temp);
			temp = temp->left;
		}
		if (r.top == -1)
			break;
		temp = r.pop();
		temp = temp->right;
	}
}
void Bin::displaypost(Node*p) {
	Node*temp = p;
	Sta r;
	while (1) {
		while (temp != NULL) {
			r.push(temp);
			temp = temp->left;
		}
		if (r.arr[r.top]->right == NULL) {
			temp = r.pop();
			cout << temp->data<<"\t";
		}
		while (r.arr[r.top]->right == temp && !r.isempty()) {
			temp = r.pop();
			cout << temp->data<<"\t";
		}
		if (r.isempty())
			break;
		temp = r.arr[r.top]->right;
	}
}
Node* Bin::rcopy(Node*b) {
	Node*temp;
	if (b != NULL) {
		temp = new Node;
		strcpy(temp->data, b->data);
		temp->left = rcopy(b->left);
		temp->right = rcopy(b->right);
	}
	return temp;
}
void Bin::operator =(Bin t2) {
	this->root = rcopy(t2.root);
}
void Bin::create() {
	int flag = 1, h;
	char ch;
	Node*temp, *curr;
	root = new Node;
	cout << "Enter root data\n";
	cin.ignore();
	cin.getline(root->data, 15);
	do {
		curr = root;
		while (flag == 1) {
			cout << "Enter 1 for left subtree,2 for right subtree,3 for exit\n";
			cin >> h;
			switch (h) {
			case 1:
				if (curr->left == NULL) {
					temp = new Node;
					curr->left = temp;
					cout << "Enter data\n";
					cin.ignore();
					cin.getline(temp->data, 15);
					flag = 0;
				} else
					curr = curr->left;
				break;
			case 2:
				if (curr->right == NULL) {
					temp = new Node;
					curr->right = temp;
					cout << "Enter data\n";
					cin.ignore();
					cin.getline(temp->data, 15);
					flag = 0;
				} else
					curr = curr->right;
				break;
			case 3:
				flag = 2;
				break;
			default:
				cout << "Enter valid choice\n";
				break;
			}
		}
		if (flag == 2)
			ch = 'n';
		else {
			cout << "Do you wish to continue tree creation\n";
			cin >> ch;
			flag = 1;
		}
	} while (ch == 'y');
}
void Bin::rcreate() {
	root = new Node;
	cout << "\nEnter data for root ";
	cin.ignore();
	cin.getline(root->data, 10);
	cout << "\nLevel 1";
	rcreate(root, 1);
}
void Bin::rcreate(Node*parent, int level) {
	Node *temp;
	char choice;
	level++;
	cout << "\nDo you want to add left child, 1-Yes | 0-No? ";
	cin >> choice;
	if (choice == '1') {
		cout << "\nLevel " << level;
		temp = new Node;
		cout << "\nEnter data ";
		cin.ignore();
		cin.getline(temp->data, 10);
		parent->left = temp;
		rcreate(temp, level);
	}
	cout << "\nDo you want to add right child, 1-Yes | 0-No? ";
	cin >> choice;
	if (choice == '1') {
		cout << "\nLevel " << level;
		temp = new Node;
		cout << "\nEnter data ";
		cin.ignore();
		cin.getline(temp->data, 10);
		parent->right = temp;
		rcreate(temp, level);
	}
}
void Bin::rdisplayin(Node*parent) {
	if (parent->left != NULL)
		rdisplayin(parent->left);
	cout << parent->data<<"\t";
	if (parent->right != NULL)
		rdisplayin(parent->right);
}
void Bin::rdisplaypre(Node*parent) {
	cout << parent->data<<"\t";
	if (parent->left != NULL)
		rdisplayin(parent->left);
	if (parent->right != NULL)
		rdisplayin(parent->right);
}
void Bin::rdisplaypost(Node*parent) {
	if (parent->left != NULL)
		rdisplayin(parent->left);
	if (parent->right != NULL)
		rdisplayin(parent->right);
	cout << parent->data<<"\t";
}
void Bin::display() {
	int r;
	cout
			<< "Enter\n\t1 for recursive inorder\n\t2 for recursive preorder\n\t3 for recursive postorder\n\t4 for nonrecursive inorder\n\t5 for nonrecursive preorder\n\t6 for nonrecursive postorder\n";
	cin >> r;
	switch (r) {
	case 1:
		rdisplayin(root);
		break;
	case 2:
		rdisplaypre(root);
		break;
	case 3:
		rdisplaypost(root);
		break;
	case 4:
		displayin(root);
		break;
	case 5:
		displaypre(root);
		break;
	case 6:
		displaypost(root);
		break;
	default:
		cout << "Enter valid option\n";
		break;
	}
}
Bin Bin::copy() {
	Bin n;
	Sta s1, s2;
	Node*temp = root;
	Node*adder, *curr = n.root;
	Sta r, s;
	while (1) {
		while (temp != NULL) {
			strcpy(curr->data, temp->data);
			r.push(temp);
			s.push(curr);
			temp = temp->left;
			if (temp != NULL) {
				adder = new Node;
				curr->left = adder;
			}
		}
		if (r.top == -1)
			break;
		temp = r.pop();
		curr = s.pop();
		temp = temp->right;
		if (temp != NULL) {
			adder = new Node;
			curr->right = adder;
		}
	}
	return n;
}
void Bin::remove() {
	Node*temp = root;
	Sta r;
	while (1) {
		while (temp != NULL) {
			r.push(temp);
			temp = temp->left;
		}
		if (r.arr[r.top]->right == NULL) {
			temp = r.pop();
			delete temp;
		}
		while (r.arr[r.top]->right == temp && !r.isempty()) {
			temp = r.pop();
			delete temp;
		}
		if (r.isempty())
			break;
		temp = r.arr[r.top]->right;
	}
}
int main() {
	Bin a, b;
	int c, m;
	char o;
	do {
		cout
				<< "Enter\n\t1 to create binary tree\n\t2 to traverse tree\n\t3 to copy tree\n\t4 to delete tree\n";
		cin >> c;
		switch (c) {
		case 1: {
			cout << "Enter\n\t1 for recursive\n\t2 for non-recursive\n";
			cin >> m;
			switch (m) {
			case 1:
				a.rcreate();
				break;
			case 2:
				a.create();
				break;
			default:
				cout << "Enter valid option\n";
				break;
			}
			break;
		}
		case 2: {
			a.display();
			break;
		}
		case 3: {
			cout << "Enter\n\t1 for recursive\n\t2 for non-recursive\n";
			cin >> m;
			switch (m) {
			case 1:
				b = a;
				b.display();
				break;
			case 2:
				b = a.copy();
				b.display();
				break;
			default:
				cout << "Enter valid option\n";
				break;
			}
			break;
		}
		case 4: {
			a.remove();
			b.remove();
			break;
		}
		default:
			cout << "Enter valid option\n";
			break;
		}
		cout << "Do you wish to continue\n";
		cin >> o;
	} while (o == 'y');
	return 0;
}

