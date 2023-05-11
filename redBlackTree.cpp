#include <bits/stdc++.h>
using namespace std;

enum Color
{
    red,
    black
};

class Node
{
public:
    int data;
    Color color;
    Node *left;
    Node *right;
    Node *parent;
    bool isNULLLeaf;
};

void deleteCase1(Node *, Node **);

Node *createNULLLeafNode(Node *parent)
{
    Node *leaf = new Node();
    leaf->color = black;
    leaf->isNULLLeaf = true;
    leaf->parent = parent;
    return leaf;
}

Node *createBlackNode(int data)
{
    Node *node = new Node();
    node->data = data;
    node->color = black;
    node->left = createNULLLeafNode(node);
    node->right = createNULLLeafNode(node);
    return node;
}

Node *createRedNode(Node *parent, int data)
{
    Node *node = new Node();
    node->data = data;
    node->color = red;
    node->parent = parent;
    node->left = createNULLLeafNode(node);
    node->right = createNULLLeafNode(node);
    return node;
}

class RedBlackTree
{
public:
    Node *root;
    RedBlackTree()
    {
        this->root = NULL;
    }
};

void rightRotate(Node *root, bool changeColor)
{
    Node *parent = root->parent;
    root->parent = parent->parent;
    if (parent->parent != NULL)
    {
        if (parent->parent->right == parent)
        {
            parent->parent->right = root;
        }
        else
        {
            parent->parent->left = root;
        }
    }
    Node *right = root->right;
    root->right = parent;
    parent->parent = root;
    parent->left = right;
    if (right != NULL)
    {
        right->parent = parent;
    }
    if (changeColor)
    {
        root->color = black;
        parent->color = red;
    }
}

void leftRotate(Node *root, bool changeColor)
{
    Node *parent = root->parent;
    root->parent = parent->parent;
    if (parent->parent != NULL)
    {
        if (parent->parent->right == parent)
        {
            parent->parent->right = root;
        }
        else
        {
            parent->parent->left = root;
        }
    }
    Node *left = root->left;
    root->left = parent;
    parent->parent = root;
    parent->right = left;
    if (left != NULL)
    {
        left->parent = parent;
    }
    if (changeColor)
    {
        root->color = black;
        parent->color = red;
    }
}

bool isLeftChild(Node *root)
{
    Node *parent = root->parent;
    if (parent->left == root)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Node *findSiblingNode(Node *root)
{
    Node *parent = root->parent;
    if (isLeftChild(root))
    {
        return (parent->right->isNULLLeaf ? NULL : parent->right);
    }
    else
    {
        return (parent->left->isNULLLeaf ? NULL : parent->left);
    }
}

Node *insertHelp(Node *parent, Node *root, int data)
{
    if (root == NULL || root->isNULLLeaf)
    {
        if (parent != NULL)
        {
            return createRedNode(parent, data);
        }
        else
        {
            return createBlackNode(data);
        }
    }

    if (root->data == data)
    {
        cout << "Duplicate data" << endl;
        return root;
    }
    bool isLeft;
    if (root->data > data)
    {
        Node *left = insertHelp(root, root->left, data);
        if (left == root->parent)
        {
            return left;
        }
        root->left = left;
        isLeft = true;
    }
    else
    {
        Node *right = insertHelp(root, root->right, data);
        if (right == root->parent)
        {
            return right;
        }
        root->right = right;
        isLeft = false;
    }

    if (isLeft)
    {
        if (root->color == red && root->left->color == red)
        {
            Node *sibling = findSiblingNode(root);
            if (!sibling || sibling->color == black)
            {
                if (isLeftChild(root))
                {
                    rightRotate(root, true);
                }
                else
                {
                    rightRotate(root->left, false);
                    root = root->parent;
                    leftRotate(root, true);
                }
            }
            else
            {
                root->color = black;
                sibling->color = black;
                if (root->parent->parent != NULL)
                {
                    root->parent->color = red;
                }
            }
        }
    }
    else
    {
        if (root->color == red && root->right->color == red)
        {
            Node *sibling = findSiblingNode(root);
            if (!sibling || sibling->color == black)
            {
                if (!isLeftChild(root))
                {
                    leftRotate(root, true);
                }
                else
                {
                    leftRotate(root->right, false);
                    root = root->parent;
                    rightRotate(root, true);
                }
            }
            else
            {
                root->color = black;
                sibling->color = black;
                if (root->parent->parent != NULL)
                {
                    root->parent->color = red;
                }
            }
        }
    }
    return root;
}

Node *findSmallest(Node *root)
{
    Node *prev = NULL;
    while (root != NULL && !root->isNULLLeaf)
    {
        prev = root;
        root = root->left;
    }
    return prev != NULL ? prev : root;
}

void replaceNode(Node *root, Node *child, Node **treeRoot)
{
    child->parent = root->parent;
    if (root->parent == NULL)
    {
        *treeRoot = child;
    }
    else
    {
        if (isLeftChild(root))
        {
            root->parent->left = child;
        }
        else
        {
            root->parent->right = child;
        }
    }
}

void deleteCase6(Node *doubleBlackNode, Node **treeRoot)
{
    Node *siblingNode = findSiblingNode(doubleBlackNode);

    siblingNode->color = siblingNode->parent->color;
    siblingNode->parent->color = black;
    if (isLeftChild(doubleBlackNode))
    {
        siblingNode->right->color = black;
        leftRotate(siblingNode, false);
    }
    else
    {
        siblingNode->left->color = black;
        rightRotate(siblingNode, false);
    }
    if (siblingNode->parent == NULL)
    {
        *treeRoot = siblingNode;
    }
}

void deleteCase5(Node *doubleBlackNode, Node **treeRoot)
{
    Node *siblingNode = findSiblingNode(doubleBlackNode);
    if (siblingNode->color == black)
    {
        if (isLeftChild(doubleBlackNode) && siblingNode->right->color == black && siblingNode->left->color == red)
        {
            rightRotate(siblingNode->left, true);
        }
        else if (!isLeftChild(doubleBlackNode) && siblingNode->left->color == black && siblingNode->right->color == red)
        {
            leftRotate(siblingNode->right, true);
        }
    }

    deleteCase6(doubleBlackNode, treeRoot);
}

void deleteCase4(Node *doubleBlackNode, Node **treeRoot)
{
    Node *siblingNode = findSiblingNode(doubleBlackNode);

    if (doubleBlackNode->parent->color == red && siblingNode->color == black && siblingNode->left->color == black && siblingNode->right->color == black)
    {
        siblingNode->color = red;
        doubleBlackNode->parent->color = black;
        return;
    }

    else
    {
        deleteCase5(doubleBlackNode, treeRoot);
    }
}

void deleteCase3(Node *doubleBlackNode, Node **treeRoot)
{

    Node *siblingNode = findSiblingNode(doubleBlackNode);

    if (doubleBlackNode->parent->color == black && siblingNode->color == black && siblingNode->left->color == black && siblingNode->right->color == black)
    {
        siblingNode->color = red;
        deleteCase1(doubleBlackNode->parent, treeRoot);
    }
    else
    {
        deleteCase4(doubleBlackNode, treeRoot);
    }
}

void deleteCase2(Node *doubleBlackNode, Node **treeRoot)
{
    Node *siblingNode = findSiblingNode(doubleBlackNode);
    if (siblingNode->color == red)
    {
        if (isLeftChild(siblingNode))
        {
            rightRotate(siblingNode, true);
        }
        else
        {
            leftRotate(siblingNode, true);
        }
        if (siblingNode->parent == NULL)
        {
            *treeRoot = siblingNode;
        }
    }

    deleteCase3(doubleBlackNode, treeRoot);
}

void deleteCase1(Node *doubleBlackNode, Node **treeRoot)
{
    if (doubleBlackNode->parent == NULL)
    {
        *treeRoot = doubleBlackNode;
        return;
    }
    deleteCase2(doubleBlackNode, treeRoot);
}

void deleteOneChild(Node *nodeToBeDelete, Node **treeRoot)
{
    Node *child = nodeToBeDelete->right->isNULLLeaf ? nodeToBeDelete->left : nodeToBeDelete->right;
    replaceNode(nodeToBeDelete, child, treeRoot);
    if (nodeToBeDelete->color == black)
    {
        if (child->color == red)
        {
            child->color = black;
        }
        else
        {
            deleteCase1(child, treeRoot);
        }
    }
}

void deleteHelp(Node *root, int data, Node **treeRoot)
{
    if (root == NULL || root->isNULLLeaf)
    {
        return;
    }
    if (root->data == data)
    {
        if (root->right->isNULLLeaf || root->left->isNULLLeaf)
        {
            deleteOneChild(root, treeRoot);
        }
        else
        {
            Node *inorderSuccessor = findSmallest(root->right);
            root->data = inorderSuccessor->data;
            deleteHelp(root->right, inorderSuccessor->data, treeRoot);
        }
    }
    if (root->data < data)
    {
        deleteHelp(root->right, data, treeRoot);
    }
    else
    {
        deleteHelp(root->left, data, treeRoot);
    }
}

Node *insert(Node *&root, int data)
{
    return root = insertHelp(NULL, root, data);
}

Node *deleteByValue(Node *&root, int data)
{
    Node *treeRoot = root;
    deleteHelp(root, data, &treeRoot);
    return treeRoot;
}

void inOrder(Node *root)
{
    if (root == NULL || root->isNULLLeaf)
        return;
    inOrder(root->left);
    cout << root->data << "  " << root->color << endl;
    inOrder(root->right);
}

void printRedBlackTree(Node *root, int space)
{
    if (root == NULL || root->isNULLLeaf)
    {
        return;
    }
    printRedBlackTree(root->right, space + 5);
    for (int i = 0; i < space; i++)
    {
        cout << " ";
    }
    cout << root->data << " " << (root->color == black ? "b" : "r") << endl;
    printRedBlackTree(root->left, space + 5);
}

int main()
{
    RedBlackTree *tree = new RedBlackTree();

    Node *root = tree->root;
    root = insert(root, 10);
    root = insert(root, 15);
    root = insert(root, -10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, -15);
    root = insert(root, 25);
    root = insert(root, 17);
    root = insert(root, 21);
    root = insert(root, 24);
    root = insert(root, 28);
    root = insert(root, 34);
    root = insert(root, 32);
    root = insert(root, 26);
    root = insert(root, 35);
    root = insert(root, 19);

    root = deleteByValue(root, 50);
    root = deleteByValue(root, 40);
    root = deleteByValue(root, -10);
    root = deleteByValue(root, 15);
    root = deleteByValue(root, 17);
    root = deleteByValue(root, 24);
    root = deleteByValue(root, 21);
    root = deleteByValue(root, 32);
    root = deleteByValue(root, 26);
    root = deleteByValue(root, 19);
    root = deleteByValue(root, 25);
    root = deleteByValue(root, 17);
    root = deleteByValue(root, -15);
    root = deleteByValue(root, 20);
    root = deleteByValue(root, 35);
    root = deleteByValue(root, 34);
    root = deleteByValue(root, 30);
    root = deleteByValue(root, 28);
    root = deleteByValue(root, 10);
    printRedBlackTree(root, 0);

    return 0;
}