#include <iostream>
using namespace std;

struct Node
{
	int data;
	int order;
	Node *sibling;
	Node *parent;
	Node *child;
};

// implement binomial heap
class BinomialHeap
{
private:
	Node *head;

public:
	BinomialHeap()
	{
		head = NULL;
	}
	~BinomialHeap()
	{
		// delete all nodes
	}
	void insert(int data)
	{
		// create a new node
		Node *newNode = new Node;
		newNode->data = data;
		newNode->order = 0;
		newNode->sibling = NULL;
		newNode->parent = NULL;
		newNode->child = NULL;
		// merge the new node with the heap
		// merge(newNode);
	}
};

// test binomial heap

// int main()
// {
// 	BinomialHeap bh;
// 	bh.print();
// 	bh.insert(1);
// 	bh.print();
// 	bh.insert(2);
// 	bh.print();
// 	bh.insert(3);
// 	bh.print();
// 	bh.insert(4);
// 	bh.print();
// 	bh.insert(5);
// 	bh.print();
// 	bh.insert(6);
// 	bh.print();
// 	bh.insert(7);
// 	bh.print();
// 	bh.insert(8);
// 	bh.print();
// 	bh.insert(9);
// 	bh.print();
// 	bh.insert(10);
// 	bh.print();
// 	bh.insert(11);
// 	bh.print();
// 	bh.insert(12);
// 	bh.print();
// 	bh.insert(13);
// 	bh.print();
// 	bh.insert(14);
// 	bh.print();
// 	bh.insert(15);
// 	bh.print();
// 	bh.insert(16);
// 	bh.print();
// 	bh.insert(17);
// 	bh.print();
// 	bh.insert(18);
// 	bh.print();
// 	bh.insert(19);
// 	bh.print();
// 	bh.insert(20);
// 	bh.print();
// 	bh.insert(21);
// 	bh.print();
// 	bh.insert(22);
// 	bh.print();
// 	bh.insert(23);
// 	bh.print();
// 	bh.insert(24);
// 	bh.print();
// 	bh.insert(25);
// 	bh.print();
// 	bh.insert(26);
// 	bh.print();
// 	bh.insert(27);
// 	bh.print();
// 	bh.insert(28);
// 	bh.print();
// 	bh.insert(29);
// 	bh.print();
// 	bh.insert(30);
// 	bh.print();
// 	bh.insert(31);
// 	bh.print();
// 	bh.insert(32);
// 	bh.print();
// 	bh.insert(33);
// 	bh.print();
// 	bh.insert(34);
// 	bh.print();
// 	bh.insert(35);
// 	bh.print();
// 	bh.insert(36);
// 	bh.print();
// 	bh.insert(37);
// 	bh.print();
// 	bh.insert(38);
// 	bh.print();
// 	bh.insert(39);
// 	bh.print();
// 	bh.insert(40);
// 	bh.print();
// 	bh.insert(41);
// }
