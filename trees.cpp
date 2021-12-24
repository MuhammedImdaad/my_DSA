#include <iostream>
#include <queue>
#include <climits>

using namespace std;

struct Node
{
    int data;
    Node *right;
    Node *left;
};

class Tree
{
    Node *getNode(int &elem)
    {
        Node *newNode = new Node;
        newNode->data = elem;
        newNode->left = newNode->right = NULL;
        return newNode;
    };

public:
    Node *root = NULL;
    void insert(Node **rootPtr, int elem);
    bool search(Node *root, int elem);
    Node* findMin(Node *root);
    int findMax();
    int findHeight(Node *root);
    void leverOrder();
    void inOrder(Node *root);
    void preOrder(Node *root);
    void postOrder(Node *root);
    bool isBST(Node *root, int min = INT_MIN, int max = INT_MAX);
    void deleteNode(Node** rootPtr, int elem);
};


void Tree::deleteNode(Node** rootPtr, int elem)
{
    Node*& root = *rootPtr; //root is an alias to what is pointed by rootPtr, now instead of using *rootPtr, can use root
    if (root==NULL) return;
    if (root->data > elem) deleteNode(&root->left, elem);
    else if (root->data < elem) deleteNode(&root->right, elem);
    else
    {
        if (root->right==NULL && root->left==NULL)
        {
            cout << "\ndeleted " << root->data << " node\n";
            delete root;
            root = NULL;
        }
        else if (root->left==NULL)
        {
            Node* temp = root;
            root = root->right;
            cout << "\ndeleted " << root->data << " node\n";
            delete temp;
        }
        else if (root->right==NULL)
        {
            Node* temp = root;
            root = root->left;
            cout << "\ndeleted " << root->data << " node\n";
            delete temp;
        }
        else 
        {
            Node* minNode = findMin(root->right);
            cout << "\nupdated " << root->data << " node by " << minNode->data << " node\n";
            root->data = minNode->data;
            deleteNode(&root->right, minNode->data);

        }
    }
}


bool Tree::isBST(Node *root, int min, int max)
{
    if (root == NULL)
        return true;
    if ((root->data > min) && 
        (root->data <= max) && //since duplicates were allowed, the value should be greater than the left but can be smaller or equal to the left 
        /*   (4) (1,5]
             / \
            /  (5) (4,5]
           /
         (3) (1,4]
        */
        isBST(root->right, root->data, max) &&
        isBST(root->left, min, root->data))
        return true;
    else
        return false;
}

/*traverse the tree in [left, node, right] */
void Tree::inOrder(Node *root)
{
    if (root == NULL)
        return;
    if (root->left != NULL)
        inOrder(root->left);
    cout << root->data << " ";
    if (root->right != NULL)
        inOrder(root->right);
}

/*traverse the tree in [node, left, right] */
void Tree::preOrder(Node *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

/*traverse the tree in [left, right, node] */
void Tree::postOrder(Node *root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

/*traverse the tree in breath first */
void Tree::leverOrder()
{
    if (root == NULL)
        return;
    cout << "\nLevel order (Breath first) traversal\n";
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        //when a node is visited, add its children to the queue
        Node *curNode = q.front();
        cout << curNode->data << " ";
        if (curNode->left != NULL)
            q.push(curNode->left);
        if (curNode->right != NULL)
            q.push(curNode->right);
        q.pop();
    }
    cout << endl;
}

/* find the root height which is the maximum distance between a root and the a leaf*/
int Tree::findHeight(Node *root)
{
    //a leaf node will have a height of 0
    if (root == NULL)
    {
        return -1;
    }
    //return 1 + maximum height of right or left subtree
    return 1 + std::max(findHeight(root->left), findHeight(root->right));
}

/* find the minimum element in the BST*/
Node* Tree::findMin(Node *curRoot)
{
    if (curRoot == NULL)
    {
        cout << "empty list\n";
        return NULL;
    }
    //move to the left most node, it will contain the minimum value
    while (curRoot->left != NULL)
    {
        curRoot = curRoot->left;
    }
    cout << "min of BST : " << curRoot->data << endl;
    return curRoot;
}

/* find the maximum element in the BST*/
int Tree::findMax()
{
    Node *curRoot = root;
    if (curRoot == NULL)
    {
        cout << "empty list\n";
        return -1;
    }
    //move to the right most node, it will contain the maximum value
    while (curRoot->right != NULL)
    {
        curRoot = curRoot->right;
    }
    cout << "max of BST : " << curRoot->data << endl;
    return curRoot->data;
}

/* insert an element to BST */
void Tree::insert(Node **rootPtr, int elem)
{
    Node*& root = *rootPtr; //root is an alias to what is pointed by rootPtr, now instead of using *rootPtr, can use root
    if (root == NULL)
    {
        //root will point to new node
        root = getNode(elem);
        cout << "inserted node " << elem << endl;
    }

    else if (elem <= (root)->data)
    {
        //for left subtree root->left will be the root
        insert(&(root)->left, elem);
    }
    else
    {
        //for right subtree root->right will be the root
        insert(&(root)->right, elem);
    }
}

/* find if an element is contained in the BST*/
bool Tree::search(Node *curroot, int elem)
{
    if (curroot == NULL)
    {
        cout << elem << " not found\n";
        return false;
    }
    if (curroot->data == elem)
    {
        cout << "found " << elem << endl;
        return true;
    }
    //if value is not found in the root, search in right subtree if elem is greater than root->data
    if (curroot->data < elem)
    {
        return search(curroot->right, elem);
    }
    else
        return search(curroot->left, elem);
}


int main()
{
    Tree t;
    int a[] = {1, 5, 4, 3, 5, 6, 1, 3};
    for (auto &i : a)
    {
        t.insert(&t.root, i);
    }
    int b[5] = {1, 10, 4, 8, 5};
    for (auto &i : b)
    {
        t.search(t.root, i);
    }
    t.findMin(t.root);
    t.findMax();
    cout << "height of the BST : " << t.findHeight(t.root);
    t.leverOrder();
    cout << "\nIn Order traversal\n";
    t.inOrder(t.root);
    cout << "\nPre Order traversal\n";
    t.preOrder(t.root);
    cout << "\nPost Order traversal\n";
    t.postOrder(t.root);

    t.deleteNode(&t.root, 3);
    t.leverOrder();
    t.deleteNode(&t.root, 6);
    t.leverOrder();
    t.deleteNode(&t.root, 1);
    t.leverOrder();
    t.isBST(t.root) ? cout << "\ntree is BST\n" : cout << "\ntree is not BST\n";
}