#include <iostream>

class BST
{
    struct Node
    {
        int val;
        Node *left;
        Node *right;

        Node(int val)
            : val(val), left(nullptr), right(nullptr) {}
    };

    Node *root = nullptr;

    Node *insert(int val, Node *node)
    {
        if (node == nullptr)
            return new Node(val);

        if (node->val < val)
            node->right = insert(val, node->right);
        else if (node->val > val)
            node->left = insert(val, node->left);

        return node;
    }

    void inOrder(Node *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        std::cout << node->val << " ";
        inOrder(node->right);
    }

    Node *findSuccessor(Node *node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node *remove(int val, Node *node)
    {
        if (node == nullptr)
            return node;

        if (node->val < val)
            node->right = remove(val, node->right);
        else if (node->val > val)
            node->left = remove(val, node->left);
        else
        {
            if (node->left && node->right)
            {
                Node *successor = findSuccessor(node->right);
                node->val = successor->val;
                node->right = remove(node->val, node->right);
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

    bool search(int val, Node* node)
    {
        if (node == nullptr)
            return false;
        
        if (node->val < val)
            return search(val, node->right);
        else if (node->val > val)
            return search(val, node->left);
        return true;
    }

    void deleteTree(Node* node)
    {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    void insert(int val)
    {
        root = insert(val, root);
    }

    void inOrder()
    {
        std::cout << "In Order traversal\n";
        inOrder(root);
        std::cout << std::endl;
    }

    void remove(int val)
    {
        root = remove(val, root);
    }

    ~BST()
    {
        deleteTree(root);
    }

    bool search(int val)
    {
        return search(val, root);
    }
};

int main()
{
    BST bst;
    int a[] = {10, 8, 15, 9, 11};
    for (auto &i : a)
    {
        bst.insert(i);
    }
    bst.inOrder();
    bst.remove(10);
    bst.inOrder();

    std::cout << (bst.search(11) ? "value exist\n" : "value do not exit\n");
}