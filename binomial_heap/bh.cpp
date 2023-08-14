#include <iostream>
#include <queue>
#include <cmath>
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
	int size;
	// queue<Node *> Q;

public:
	BinomialHeap()
	{
		head = NULL;

		size = 0;
	}
	~BinomialHeap()
	{
		// delete all nodes
	}
	Node *node_initialization(int data)
	{
		// create a new node
		Node *newNode = new Node;
		newNode->data = data;
		newNode->order = 0;
		newNode->sibling = NULL;
		newNode->parent = NULL;
		newNode->child = NULL;

		return newNode;
	}

	void insert(int data)
	{
		BinomialHeap bh;
		bh.head = this->node_initialization(data);
		//*this = Union(bh);
		BinomialHeap newHeap = this->Union(bh);
		this->size++;
		this->head = newHeap.head;
		// cout << "Inserted " << data << " into the heap" << endl;
	}

	BinomialHeap Union(BinomialHeap bh1)
	{
		BinomialHeap newHeap = this->mergeForest(*this, bh1);

		if (!newHeap.head)
			return newHeap;

		Node *prev = nullptr;
		Node *curr = newHeap.head;
		Node *next = curr->sibling;

		while (next)
		{
			bool currentTwoRootsAreNotEqual = curr->order != next->order;
			bool nextTwoRootsAreEqual = next->sibling && next->order == next->sibling->order;
			bool movePointers = currentTwoRootsAreNotEqual || nextTwoRootsAreEqual;

			if (movePointers)
			{
				prev = curr;
				curr = next;
			}
			else
			{
				if (curr->data <= next->data)
				{
					curr->sibling = next->sibling;
					this->linkTree(curr, next);
				}
				else
				{
					if (!prev)
						newHeap.head = next;
					else
						prev->sibling = next;

					this->linkTree(next, curr);
					curr = next;
				}
			}

			next = curr->sibling;
		}

		return newHeap;
	};

	void linkTree(Node *parent, Node *child)
	{
		child->parent = parent;
		child->sibling = parent->child;
		parent->child = child;
		parent->order++;
	}

	BinomialHeap mergeForest(BinomialHeap self, BinomialHeap bh1)
	{
		if (!self.head)
			return bh1;
		if (!bh1.head)
			return self;

		Node *a = self.head;
		Node *b = bh1.head;
		Node *head = nullptr;

		if (a->order <= b->order)
		{
			head = a;
			a = a->sibling;
		}
		else
		{
			head = b;
			b = b->sibling;
		}

		Node *curr = head;

		while (a && b)
		{
			if (a->order <= b->order)
			{
				curr->sibling = a;
				a = a->sibling;
			}
			else
			{
				curr->sibling = b;
				b = b->sibling;
			}
			curr = curr->sibling;
		}

		if (a)
			curr->sibling = a;
		else
			curr->sibling = b;

		BinomialHeap mergedHeap = BinomialHeap();
		mergedHeap.head = head;
		mergedHeap.size = self.size + bh1.size;

		return mergedHeap;
	}

	queue<Node *> nextQ;

	void print()
	{
		cout << "Printing Binomial Heap..." << endl;
		if (!this->head)
		{
			cout << "Heap is empty" << endl;
			return;
		}

		Node *curr = this->head;
		while (curr)
		{
			cout << "Binomial Tree, B" << curr->order << endl;
			cout << "Level 0 : " << curr->data << " " << endl;
			queue<Node *> Q;
			if (curr->child)
			{
				Q.push(curr->child);
				cout << "Level 1 : ";
			}
			int i = 2;

			while (!Q.empty())
			{
				Node *child = Q.front();
				Q.pop();
				this->printTree(child, Q);

				if (Q.size() == 0 && nextQ.size() != 0)
				{
					cout << endl;
					cout << "Level " << i << " : ";
					i++;
					swap(Q, nextQ);
				}
				else if (Q.size() == 0 && nextQ.size() == 0)
					cout << endl;
			}

			curr = curr->sibling;
		}
	}

	void printTree(Node *node, queue<Node *> &Q)
	{
		if (!node)
			return;

		// print the tree level by level

		Node *curr = node;
		while (curr)
		{
			cout << curr->data << " ";
			if (curr->child)
				nextQ.push(curr->child);
			curr = curr->sibling;
		}
		// cout << endl;

		// while (!Q.empty())
		// {
		// 	Node *temp = Q.front();
		// 	Q.pop();
		// 	this->printTree(temp);
		// }

		// 	curr = node;
		// while (curr)
		// {
		// 	this->printTree(curr->child);
		// 	curr = curr->sibling;
		// }
	}

	Node *findMin()
	{
		if (!this->head)
			return nullptr;

		Node *curr = this->head;
		Node *minNode = curr;
		int min = curr->data;

		while (curr)
		{
			if (curr->data < min)
			{
				min = curr->data;
				minNode = curr;
			}
			curr = curr->sibling;
		}

		return minNode;
	}

	Node *reverse(Node *node)
	{
		if (!node)
			return nullptr;

		Node *curr = node;
		Node *prev = nullptr;
		Node *next = nullptr;

		while (curr)
		{
			next = curr->sibling;
			curr->sibling = prev;
			prev = curr;
			curr = next;
		}

		return prev;
	}

	int extractMin()
	{
		if (!this->head)
			return -1;

		Node *curr = this->head;
		Node *minNode = curr;
		Node *prev = nullptr;
		Node *prevMinNode = nullptr;
		int min = curr->data;

		while (curr)
		{
			if (curr->data < min)
			{
				min = curr->data;
				minNode = curr;
				prevMinNode = prev;
			}
			prev = curr;
			curr = curr->sibling;
		}

		if (!prevMinNode)
			this->head = minNode->sibling;
		else
			prevMinNode->sibling = minNode->sibling;

		Node *child = minNode->child;

		if (child == nullptr)
			return minNode->data;

		while (child)
		{
			child->parent = nullptr;
			child = child->sibling;
		}

		minNode->child = reverse(minNode->child);

		BinomialHeap newHeap = BinomialHeap();
		newHeap.head = minNode->child;
		newHeap.size = pow(2, minNode->order) - 1;
		this->size -= newHeap.size + 1;

		BinomialHeap mergedHeap = this->Union(newHeap); // sort the heap by asec
		this->head = mergedHeap.head;
		this->size = mergedHeap.size;

		return minNode->data;
	}
};

// test binomial heap

// int main()
// {
// 	// freopen("input.txt", "r", stdin);
// 	freopen("output.txt", "w", stdout);
// 	BinomialHeap bh;
// 	BinomialHeap bh1;
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
// 	bh1.insert(11);
// 	bh1.print();
// 	bh1.insert(12);
// 	bh1.print();
// 	bh1.insert(13);
// 	bh1.print();
// 	bh1.insert(14);
// 	bh1.print();
// 	bh1.insert(15);
// 	bh1.print();
// 	bh1.insert(16);
// 	bh1.print();
// 	bh1.insert(17);
// 	bh1.print();
// 	bh = bh.Union(bh1);
// 	cout << "print" << endl;
// 	bh.print();
// bh.insert(18);
// bh.print();
// bh.insert(19);
// bh.print();
// bh.insert(20);
// bh.print();
// bh.insert(21);
// bh.print();
// bh.insert(22);
// bh.print();
// bh.insert(23);
// bh.print();
// bh.insert(24);
// bh.print();
// bh.insert(25);
// bh.print();
// bh.insert(26);
// bh.print();
// bh.insert(27);
// bh.print();
// bh.insert(28);
// bh.print();
// bh.insert(29);
// bh.print();
// bh.insert(30);
// bh.print();
// bh.insert(31);
// bh.print();
// bh.insert(32);
// bh.print();
// bh.insert(33);
// bh.print();
// bh.insert(34);
// bh.print();
// bh.insert(35);
// bh.print();
// bh.insert(36);
// bh.print();
// bh.insert(37);
// bh.print();
// bh.insert(38);
// bh.print();
// bh.insert(39);
// bh.print();
// bh.insert(40);
// bh.print();
// bh.insert(41);
//}

int main()
{
	freopen("ios/in9.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	BinomialHeap bh;
	string s;
	// cin >> s;

	while (cin >> s)
	{
		if (s == "I")
		{
			int x;
			cin >> x;
			bh.insert(x);
		}
		else if (s == "E")
		{
			cout << "Extract-Min returned " << bh.extractMin() << endl;
		}
		else if (s == "F")
		{
			Node *minNode = bh.findMin();
			if (minNode)
				cout << "Find-Min returned " << minNode->data << endl;
			else
				cout << "Heap is empty" << endl;
		}
		else if (s == "P")
		{
			bh.print();
		}
		else if (s == "U")
		{
			int a;
			BinomialHeap bh1;
			while (cin >> a)
			{
				bh1.insert(a);
			}
			bh = bh.Union(bh1);
			// cout << bh.findMin()->data << endl;
			cin.clear();
			fflush(stdin);
			//  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		// cin >> s;
		// cout << s << endl;
	}
}