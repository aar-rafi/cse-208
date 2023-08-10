#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

// AVL Tree Node
struct Node
{
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of a node
int getHeight(Node *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to get the balance factor of a node
int getBalanceFactor(Node *node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to update the height of a node
void updateHeight(Node *node)
{
    if (node == nullptr)
        return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// Function to perform a right rotation
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

// Function to perform a left rotation
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

// Function to balance the AVL tree
Node *balance(Node *node)
{
    if (node == nullptr)
        return nullptr;

    updateHeight(node);
    int balanceFactor = getBalanceFactor(node);

    // Left-Left case
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
        return rightRotate(node);

    // Right-Right case
    if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
        return leftRotate(node);

    // Left-Right case
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-Left case
    if (balanceFactor < -1 && getBalanceFactor(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to insert a key into the AVL tree
Node *insert(Node *root, int key)
{
    if (root == nullptr)
        return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // Duplicate keys not allowed

    return balance(root);
}

// Function to find the node with minimum key value
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

// Function to find a key in the AVL tree
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

// Function to perform an in-order traversal of the AVL tree
void inOrderTraversal(Node *root)
{
    if (root == nullptr)
        return;

    inOrderTraversal(root->left);
    // outFile << root->key << " ";
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
    freopen("in.txt", "r", stdin);
    freopen("out_avl.txt", "w", stdout);
    // ifstream inFile("in.txt");
    // ofstream outFile("out_avl.txt");
    ofstream reportFile("report_avl.txt");

    string operation;
    int key;

    Node *root = nullptr;
    std::chrono::duration<double, std::milli> iTime = std::chrono::duration<double, std::milli>::zero();
    std::chrono::duration<double, std::milli> dTime = std::chrono::duration<double, std::milli>::zero();
    std::chrono::duration<double, std::milli> fTime = std::chrono::duration<double, std::milli>::zero();
    std::chrono::duration<double, std::milli> tTime = std::chrono::duration<double, std::milli>::zero();

    while (cin >> operation)
    {

        if (operation == "I")
        {
            // inFile >> key;
            cin >> key;
            auto start = chrono::high_resolution_clock::now();
            root = insert(root, key);
            auto stop = chrono::high_resolution_clock::now();
            iTime += (stop - start);
            preOrderTraversal(root);
            // outFile << endl;
            cout << endl;
        }
        else if (operation == "D")
        {
            // inFile >> key;
            cin >> key;
            auto start = chrono::high_resolution_clock::now();
            root = deleteNode(root, key);
            auto stop = chrono::high_resolution_clock::now();
            dTime += (stop - start);
            preOrderTraversal(root);
            // outFile << endl;
            cout << endl;
        }
        else if (operation == "F")
        {
            // inFile >> key;
            cin >> key;
            auto start = chrono::high_resolution_clock::now();
            if (find(root, key))
                // outFile << "found" << endl;
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
            // outFile << endl;
            cout << endl;
        }

        //     auto stop = chrono::high_resolution_clock::now();
        //     auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
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
