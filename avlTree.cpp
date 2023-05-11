#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    int height;

    Node(int data)
    {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->height = 1;
    };
};

int getHeight(Node *node)
{

    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

int balanceFactor(Node *node)
{

    if (node == NULL)
    {
        return 0;
    }
    return (getHeight(node->left) - getHeight(node->right));
}

Node *leftRotate(Node *node)
{

    Node *x = node->right;
    Node *temp = x->left;

    x->left = node;
    node->right = temp;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Node *rightRotate(Node *node)
{

    Node *x = node->left;
    Node *temp = x->right;

    x->right = node;
    node->left = temp;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Node *minValueNode(Node *node)
{
    Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

Node *insertToAVL(Node *node, int data)
{
    if (node == NULL)
        return new Node(data);

    if (node->data > data)
        node->left = insertToAVL(node->left, data);

    else if (node->data < data)
        node->right = insertToAVL(node->right, data);

    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 and data < node->left->data)
        return rightRotate(node);

    if (balance < -1 and data > node->right->data)
        return leftRotate(node);

    if (balance > 1 and data > node->left->data)
    {

        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 and data < node->right->data)
    {

        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) ||
            (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {
            Node *temp = minValueNode(root->right);

            root->data = temp->data;

            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && balanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && balanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inOrderTraversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    inOrderTraversal(root->left);
    cout << root->data << endl;
    inOrderTraversal(root->right);
}

void preOrderTraversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->data << endl;
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void postOrderTraversal(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->data << endl;
}

void printTree(Node *root, int space)
{
    if (root == NULL)
    {
        return;
    }
    printTree(root->right, space + 5);
    for (int i = 0; i < space; i++)
    {
        cout << " ";
    }
    cout << root->data << " " << endl;
    printTree(root->left, space + 5);
}

int main()
{
    Node *root;
    root = insertToAVL(root, 10);
    root = insertToAVL(root, 15);
    root = insertToAVL(root, -10);
    root = insertToAVL(root, 20);
    root = insertToAVL(root, 30);
    root = insertToAVL(root, 40);
    root = insertToAVL(root, 50);
    root = insertToAVL(root, -15);
    root = insertToAVL(root, 25);
    root = insertToAVL(root, 17);
    root = insertToAVL(root, 21);
    root = insertToAVL(root, 24);
    root = insertToAVL(root, 28);
    root = insertToAVL(root, 34);
    root = insertToAVL(root, 32);
    root = insertToAVL(root, 26);
    root = insertToAVL(root, 35);
    root = insertToAVL(root, 19);

    root = deleteNode(root, 50);
    // // System.out.println(redBlackTree.validateRedBlackTree(root));
    root = deleteNode(root, 40);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    root = deleteNode(root, -10);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    root = deleteNode(root, 15);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    root = deleteNode(root, 17);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    root = deleteNode(root, 24);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    root = deleteNode(root, 21);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    root = deleteNode(root, 32);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    root = deleteNode(root, 50);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteNode(root, 50);
    // // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteNode(root, 50);
    // // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteNode(root, 50);
    // // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteNode(root, 50);
    // // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteNode(root, 50);
    // // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteNode(root, 50);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteByValue(root, 34);
    // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteByValue(root, 30);
    // // // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // root = deleteByValue(root, 28);
    // // // // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // // root = deleteByValue(root, 30);
    // // cout << root->data << endl;
    // // root = deleteByValue(root, 10);
    // // System.out.println(redBlackTree.validateRedBlackTree(root));
    // if (root->parent == NULL)
    // {
    //     cout << "Null parent\n";
    // }
    printTree(root, 0);
    inOrderTraversal(root);

    return 0;
}