#include <iostream>
#include <cstdlib> // For rand()

class RedBlackTree
{
    struct Node
    {
        int value;
        Node *left;
        Node *right;
        Node *parent;
        bool isRed;

        Node(int key, bool isRed = true)
            : value(key), parent(nullptr),left(nullptr), right(nullptr), isRed(isRed) {}
    };

    Node *root;

    void leftRotate(Node *x)
    {
        Node* y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x->parent->left == x)
            x->parent->left = y;
        else 
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    /*
              |             |
              x             y
             / \           / \ 
            y  T1   =>    T2  x  
           / \               / \
          T2 T3             T3 T1
    */
    void rightRotate(Node *x)
    {
        Node* y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x->parent->right == x)
            x->parent->right = y;
        else 
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void RBInsertFixUp(Node* node)
    {
        // enters a loop iteration only if z:p is red, we know that then z:p cannot be the root. Hence, z:p:p exists
        while (node->parent != nullptr && node->parent->isRed) 
        {
            Node* grand = node->parent->parent;
            // Parent is the left child of grandparent
            if (grand->left == node->parent)
            {
                Node* uncle = grand->right;
                if (uncle != nullptr && uncle->isRed) // Case 1: Uncle is red
                {
                    node->parent->isRed = uncle->isRed = false;
                    grand->isRed = true;
                    node = grand; // Move up to check the rest of the tree
                }
                else
                {
                    //uncle is black (NILs are black (leaf))
                    if (node->parent->right == node) // Case 2: Node is right child
                    {
                        node = node->parent;
                        leftRotate(node); // Convert to Case 3
                    }

                    // Case 3: Node is left child
                    node->parent->isRed = false; //node parent is set to black
                    grand->isRed = true;
                    rightRotate(grand); 
                }
            }   
            else
            {
                Node* uncle = grand->left;
                if (uncle != nullptr && uncle->isRed)
                {
                    node->parent->isRed = uncle->isRed = false;
                    grand->isRed = true;
                    node = grand; 
                }
                else
                {
                    if (node->parent->left == node)
                    {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->isRed = false; 
                    grand->isRed = true;
                    leftRotate(grand);
                }
            }
        } //if node parent is black loop terminates

        root->isRed = false;
    }

    void RBInsert(Node *node)
    {
        Node* curr = root;
        Node* parent = nullptr;
        
        while(curr != nullptr)
        {
            parent = curr;
            if (curr->value < node->value)
                curr = curr->right;
            else
                curr = curr->left;
        }

        node->parent = parent;

        if (parent == nullptr)
            root = node;
        else if (parent->value < node->value)
            parent->right = node;
        else 
            parent->left = node;
        
        RBInsertFixUp(node);
    }

    void inOrder(Node *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        std::cout << node->value << " ";
        inOrder(node->right);
    }

    bool search(Node *node, int key)
    {
        if (node == nullptr)
            return false;

        if (node->value < key)
            return search(node->right, key);
        else if (node->value > key)
            return search(node->left, key);
        return true;
    }


    void RBRemove(int key)
    {

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
    RedBlackTree() : root(nullptr){}

    ~RedBlackTree()
    {
        deleteTree(root);
    }

    void insert(int key)
    {
        RBInsert(new Node(key));
    }

    void remove(int key)
    {
        RBRemove(key);
    }

    bool search(int key)
    {
        return search(root, key);
    }

    void inOrder()
    {
        std::cout << "In-order traversal of RedBlackTree:\n";
        inOrder(root);
        std::cout << std::endl;
    }
};

int main()
{
    RedBlackTree redBlackTree;

    // Insert elements into the Treap
    int keys[] = {5, 2, 10, 1, 8, 7, 3};
    for (int key : keys)
    {
        redBlackTree.insert(key);
    }

    // Print the redBlackTree
    redBlackTree.inOrder();

    // Search for an element
    int searchKey = 10;
    std::cout << "Searching for " << searchKey << ": "
              << (redBlackTree.search(searchKey) ? "Found" : "Not Found") << std::endl;

    // Delete an element
    // int deleteKey = 5;
    // std::cout << "Deleting " << deleteKey << "...\n";
    // redBlackTree.remove(deleteKey);
    // redBlackTree.inOrder();

    return 0;
}
