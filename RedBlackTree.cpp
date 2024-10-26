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

        Node(int key, bool isRed = true, Node* NIL = nullptr)
            : value(key), parent(NIL), left(NIL), right(NIL), isRed(isRed) {}
    };

    Node *root;
    Node *NIL; //sentinel

    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == NIL)
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
        Node *y = x->left;
        x->left = y->right;

        if (y->right != NIL)
            y->right->parent = x;

        y->parent = x->parent;
        if (x->parent == NIL)
            root = y;
        else if (x->parent->right == x)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void RBInsertFixUp(Node *node)
    {
        // enters a loop iteration only if z:p is red, we know that then z:p cannot be the root. Hence, z:p:p exists
        while (node->parent != NIL && node->parent->isRed)
        {
            Node *grand = node->parent->parent;
            // Parent is the left child of grandparent
            if (grand->left == node->parent)
            {
                Node *uncle = grand->right;
                if (uncle->isRed) // Case 1: Uncle is red
                {
                    node->parent->isRed = uncle->isRed = false;
                    grand->isRed = true;
                    node = grand; // Move up to check the rest of the tree
                }
                else
                {
                    // uncle is black (NILs are black (leaf))
                    if (node->parent->right == node) // Case 2: Node is right child
                    {
                        node = node->parent;
                        leftRotate(node); // Convert to Case 3
                    }

                    // Case 3: Node is left child
                    node->parent->isRed = false; // node parent is set to black
                    grand->isRed = true;
                    rightRotate(grand);
                }
            }
            else
            {
                Node *uncle = grand->left;
                if (uncle->isRed)
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
        } // if node parent is black loop terminates

        root->isRed = false;
    }

    void RBInsert(Node *node)
    {
        Node *curr = root;
        Node *parent = NIL;

        while (curr != NIL)
        {
            parent = curr;
            if (curr->value < node->value)
                curr = curr->right;
            else if (curr->value > node->value)
                curr = curr->left;
            else 
                return;
        }

        node->parent = parent;

        if (parent == NIL)
            root = node;
        else if (parent->value < node->value)
            parent->right = node;
        else
            parent->left = node;

        RBInsertFixUp(node);
    }

    void inOrder(Node *node)
    {
        if (node == NIL)
            return;
        inOrder(node->left);
        std::cout << node->value << " ";
        inOrder(node->right);
    }

    bool search(Node *node, int key)
    {
        if (node == NIL)
            return false;

        if (node->value < key)
            return search(node->right, key);
        else if (node->value > key)
            return search(node->left, key);
        return true;
    }

    Node *findSuccessor(Node *node)
    {
        while (node && node->left != NIL)
            node = node->left;
        return node;
    }

    // replaces the subtree rooted at node u by the subtree rooted at node v
    void transPlant(Node *u, Node *v)
    {
        if (u == root)
            root = v;
        else if (u->parent->left == u)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent; //assign to v:p even if v points to the sentinel
    }

    void RBRemoveFixUp(Node *x)
    {
        while (x != root && x->isRed == false)
        {
            if (x == x->parent->left) // is x a left child?
            {
                Node *w = x->parent->right; // w is x’s sibling
                if (w->isRed) // case 1
                {
                    w->isRed = false;
                    x->parent->isRed = true;
                    leftRotate(x->parent);
                    w = x->parent->right; // new w is black
                }

                if (w->left->isRed == false && w->right->isRed == false) // case 2
                {
                    w->isRed = true;
                    x = x->parent;
                }

                else
                {
                    if (w->right->isRed == false) // case 3
                    {
                        w->left->isRed = false;
                        w->isRed = true;
                        rightRotate(w);
                        w = x->parent->right;
                    }

                    w->isRed = x->parent->isRed; // case 4
                    x->parent->isRed = false;
                    w->right->isRed = false;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                Node *w = x->parent->left; // w is x’s sibling
                if (w->isRed) // case 1
                {
                    w->isRed = false;
                    x->parent->isRed = true;
                    rightRotate(x->parent);
                    w = x->parent->left; // new w is black
                }

                if (w->right->isRed == false && w->left->isRed == false) // case 2
                {
                    w->isRed = true;
                    x = x->parent;
                }

                else
                {
                    if (w->left->isRed == false) // case 3
                    {
                        w->right->isRed = false;
                        w->isRed = true;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    w->isRed = x->parent->isRed; // case 4
                    x->parent->isRed = false;
                    w->left->isRed = false;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->isRed = false;
    }

    void RBRemove(int key)
    {
        Node *curr = root;
        while (true)
        {
            if (curr == NIL)
                return;
            if (curr->value < key)
                curr = curr->right;
            else if (curr->value > key)
                curr = curr->left;
            else // node found
                break;
        }

        Node *y = curr;
        bool isOrigColY = y->isRed;
        Node *x;

        if (curr->left == NIL)
        {
            x = curr->right;
            transPlant(curr, x); // replace curr by its right child
            delete curr;
        }
        else if (curr->right == NIL)
        {
            x = curr->left;
            transPlant(curr, x); // replace curr by its left child
            delete curr;
        }
        else
        {
            // both children exist

            y = findSuccessor(curr->right); // y is curr’s successor
            isOrigColY = y->isRed;
            x = y->right; // can be T:nil

            if (y != curr->right) // is y farther down the tree?
            {     
                transPlant(y, x);       // replace y by its right child
                y->right = curr->right; // curr’s right child becomes y’s right child
                curr->right->parent = y;
            }
            else
                x->parent = y;// in case x is T:nil

            transPlant(curr, y); // replace curr by its successor y
            y->left = curr->left;    // and give curr’s left child to y which had no left child
            curr->left->parent = y;
            y->isRed = curr->isRed;
            delete curr;
        }

        if (isOrigColY == false) // if by moving black node in the tree can produce a violation, correct them. 
            RBRemoveFixUp(x);
    }

    void deleteTree(Node *node)
    {
        if (node == NIL)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    RedBlackTree()
    {
        NIL = new Node(0, false);
        root = NIL; 
    }

    ~RedBlackTree()
    {
        deleteTree(root);
        delete NIL;
    }

    void insert(int key)
    {
        RBInsert(new Node(key, true, NIL));
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
    int keys[] = {5, 2, 10, 1, 8, 7, 3, 3, 3};
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
    int deleteKey = 5;
    std::cout << "Deleting " << deleteKey << "...\n";
    redBlackTree.remove(deleteKey);
    redBlackTree.inOrder();

    return 0;
}
