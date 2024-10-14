#include <iostream>
#include <cstdlib> // For rand()

class Treap
{
    struct Node
    {
        int key;      // BST key
        int priority; // Heap priority
        Node *left;
        Node *right;

        Node(int key)
            : key(key), priority(rand()), left(nullptr), right(nullptr) {}
    };

    Node *root;
    bool maxHeap;

    Node *leftRotate(Node *node)
    {
        Node *right = node->right;
        node->right = right->left;
        right->left = node;
        return right;
    }

    Node *rightRotate(Node *node)
    {
        Node *left = node->left;
        node->left = left->right;
        left->right = node;
        return left;
    }

    Node *insert(Node *node, int key)
    {
        if (node == nullptr)
            return new Node(key);
        if (node->key < key)
        {
            node->right = insert(node->right, key);
            if ((maxHeap && node->right->priority > node->priority) ||
                (!maxHeap && node->right->priority < node->priority))
                node = leftRotate(node);
        }
        else if (node->key > key)
        {
            node->left = insert(node->left, key);
            if ((maxHeap && node->left->priority > node->priority) ||
            (!maxHeap && node->left->priority < node->priority))
                node = rightRotate(node);
        }
        return node;
    }

    void inOrder(Node *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        std::cout << "{" << node->key << " : " << node->priority / 1000000 << "} ";
        inOrder(node->right);
    }

    bool search(Node *node, int key)
    {
        if (node == nullptr)
            return false;

        if (node->key < key)
            return search(node->right, key);
        else if (node->key > key)
            return search(node->left, key);
        return true;
    }

    Node *remove(Node *node, int key)
    {
        if (node == nullptr)
            return node;

        if (node->key < key)
            node->right = remove(node->right, key);
        else if (node->key > key)
            node->left = remove(node->left, key);
        else
        {
            if (node->left && node->right)
            {
                if ((maxHeap && node->left->priority > node->right->priority) || 
                (!maxHeap && node->left->priority < node->right->priority))
                {
                    node = rightRotate(node);
                    node->right = remove(node->right, key);
                }
                else
                {
                    node = leftRotate(node);
                    node->left = remove(node->left, key);
                }
            }
            else if (node->left || node->right)
            {
                Node *deleteNode = node;
                node = node->right ? node->right : node->left;
                delete deleteNode;
            }
            else
            {
                delete node;
                node = nullptr;
            }
        }

        return node;
    }

    void deleteTree(Node *node)
    {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    Treap(bool maxHeap = true) : root(nullptr), maxHeap(maxHeap) {}

    ~Treap()
    {
        deleteTree(root);
    }

    void insert(int key)
    {
        root = insert(root, key);
    }

    void remove(int key)
    {
        root = remove(root, key);
    }

    bool search(int key)
    {
        return search(root, key);
    }

    void inOrder()
    {
        std::cout << "In-order traversal of Treap:\n";
        inOrder(root);
        std::cout << std::endl;
    }
};

int main()
{
    Treap treap;

    // Insert elements into the Treap
    int keys[] = {5, 2, 10, 1, 8, 7, 3};
    for (int key : keys)
    {
        treap.insert(key);
    }

    // Print the Treap
    treap.inOrder();

    // Search for an element
    int searchKey = 10;
    std::cout << "Searching for " << searchKey << ": "
              << (treap.search(searchKey) ? "Found" : "Not Found") << std::endl;

    // Delete an element
    int deleteKey = 5;
    std::cout << "Deleting " << deleteKey << "...\n";
    treap.remove(deleteKey);
    treap.inOrder();

    return 0;
}
