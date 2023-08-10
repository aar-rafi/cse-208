#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(Node *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalanceFactor(Node *node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node *node)
{
    if (node == nullptr)
        return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node *balance(Node *node)
{
    if (node == nullptr)
        return nullptr;

    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        return rightRotate(node);

    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        return leftRotate(node);

    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node *insert(Node *root, int key)
{
    if (root == nullptr)
        return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root;

    return balance(root);
}

Node *findMin(Node *node)
{
    while (node->left != nullptr)
        node = node->left;
    return node;
}

Node *deleteNode(Node *root, int key)
{
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (root->left == nullptr || root->right == nullptr)
        {
            Node *temp = root->left ? root->left : root->right;
            delete root;
            root = temp;
        }
        else
        {
            Node *temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    return balance(root);
}

bool find(Node *root, int key)
{
    if (root == nullptr)
        return false;
    if (key == root->key)
        return true;

    if (key < root->key)
        return find(root->left, key);
    else
        return find(root->right, key);
}

void inOrderTraversal(Node *root)
{
    if (root == nullptr)
        return;

    inOrderTraversal(root->left);
    cout << root->key << " ";
    inOrderTraversal(root->right);
}
void preOrderTraversal(Node *root)
{
    if (root == nullptr)
        return;
    cout << root->key;
    if (root->left != nullptr || root->right != nullptr)
    {
        cout << "(";
        preOrderTraversal(root->left);

        if (root->right != nullptr)
        {
            cout << ",";
            preOrderTraversal(root->right);
            cout << ")";
        }
        else
        {
            cout << ",)";
        }
    }
}

int main()
{
    freopen("../in.txt", "r", stdin);
    freopen("out_avl.txt", "w", stdout);
    ofstream reportFile("report_avl.txt");

    string operation;
    int key;

    Node *root = nullptr;
    chrono::duration<double, std::milli> iTime = chrono::duration<double, std::milli>::zero();
    chrono::duration<double, std::milli> dTime = chrono::duration<double, std::milli>::zero();
    chrono::duration<double, std::milli> fTime = chrono::duration<double, std::milli>::zero();
    chrono::duration<double, std::milli> tTime = chrono::duration<double, std::milli>::zero();

    while (cin >> operation)
    {

        if (operation == "I")
        {
            cin >> key;
            auto start = chrono::high_resolution_clock::now();
            root = insert(root, key);
            auto stop = chrono::high_resolution_clock::now();
            iTime += (stop - start);
            preOrderTraversal(root);
            cout << endl;
        }
        else if (operation == "D")
        {
            cin >> key;
            auto start = chrono::high_resolution_clock::now();
            root = deleteNode(root, key);
            auto stop = chrono::high_resolution_clock::now();
            dTime += (stop - start);
            preOrderTraversal(root);
            cout << endl;
        }
        else if (operation == "F")
        {
            cin >> key;
            auto start = chrono::high_resolution_clock::now();
            if (find(root, key))
                cout << "found" << endl;
            else
                cout << "not found" << endl;
            auto stop = chrono::high_resolution_clock::now();
            fTime += (stop - start);
        }
        else if (operation == "T")
        {
            auto start = chrono::high_resolution_clock::now();
            inOrderTraversal(root);
            auto stop = chrono::high_resolution_clock::now();
            tTime += (stop - start);
            cout << endl;
        }
    }
    reportFile << "operation time(ms)" << endl;
    reportFile << "Insert: "
               << " " << iTime.count() << endl;
    reportFile << "Delete: "
               << " " << dTime.count() << endl;
    reportFile << "Find: "
               << " " << fTime.count() << endl;
    reportFile << "Traversal: "
               << " " << tTime.count() << endl;
    reportFile << "Total: "
               << " " << iTime.count() + dTime.count() + fTime.count() + tTime.count() << endl;

    reportFile.close();

    return 0;
}
