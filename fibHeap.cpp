#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    Node *parent;
    Node *child;
    Node *left;
    Node *right;
    int key;
    int degree;
    char mark; // Black or white mark of the Node
    char c;    // Flag for assisting in the Find Node function
};

Node *mini = NULL;

int noOfNodes = 0;

void insertion(int val)
{
    Node *newNode = new Node();
    newNode->key = val;
    newNode->degree = 0;
    newNode->mark = 'W';
    newNode->c = 'N';
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->left = newNode;
    newNode->right = newNode;
    if (mini != NULL)
    {
        (mini->left)->right = newNode;
        newNode->right = mini;
        newNode->left = mini->left;
        mini->left = newNode;
        if (newNode->key < mini->key)
            mini = newNode;
    }
    else
    {
        mini = newNode;
    }
    noOfNodes++;
}
void Fibonnaci_link(Node *childPtr, Node *parentPtr)
{
    (childPtr->left)->right = childPtr->right;
    (childPtr->right)->left = childPtr->left;
    if (parentPtr->right == parentPtr)
        mini = parentPtr;
    childPtr->left = childPtr;
    childPtr->right = childPtr;
    childPtr->parent = parentPtr;
    if (parentPtr->child == NULL)
        parentPtr->child = childPtr;
    childPtr->right = parentPtr->child;
    childPtr->left = (parentPtr->child)->left;
    ((parentPtr->child)->left)->right = childPtr;
    (parentPtr->child)->left = childPtr;
    if (childPtr->key < (parentPtr->child)->key)
        parentPtr->child = childPtr;
    parentPtr->degree++;
}
// Consolidating the heap
void Consolidate()
{
    int temp1;
    float temp2 = (log(noOfNodes)) / (log(2));
    int temp3 = temp2;
    Node *arr[temp3 + 1];
    for (int i = 0; i <= temp3; i++)
        arr[i] = NULL;
    Node *ptr1 = mini;
    Node *ptr2;
    Node *ptr3;
    Node *ptr4 = ptr1;
    do
    {
        ptr4 = ptr4->right;
        temp1 = ptr1->degree;
        while (arr[temp1] != NULL)
        {
            ptr2 = arr[temp1];
            if (ptr1->key > ptr2->key)
            {
                ptr3 = ptr1;
                ptr1 = ptr2;
                ptr2 = ptr3;
            }
            if (ptr2 == mini)
                mini = ptr1;
            Fibonnaci_link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                mini = ptr1;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr1->right;
    } while (ptr1 != mini);
    mini = NULL;
    for (int j = 0; j <= temp3; j++)
    {
        if (arr[j] != NULL)
        {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (mini != NULL)
            {
                (mini->left)->right = arr[j];
                arr[j]->right = mini;
                arr[j]->left = mini->left;
                mini->left = arr[j];
                if (arr[j]->key < mini->key)
                    mini = arr[j];
            }
            else
            {
                mini = arr[j];
            }
            if (mini == NULL)
                mini = arr[j];
            else if (arr[j]->key < mini->key)
                mini = arr[j];
        }
    }
}

int Extract_min()
{
    if (mini == NULL)
    {
        cout << "The heap is empty" << endl;
        return INT_MIN;
    }

    else
    {
        int minimum = mini->key;
        Node *temp = mini;
        Node *pntr;
        pntr = temp;
        Node *x = NULL;
        if (temp->child != NULL)
        {

            x = temp->child;
            do
            {
                pntr = x->right;
                (mini->left)->right = x;
                x->right = mini;
                x->left = mini->left;
                mini->left = x;
                if (x->key < mini->key)
                    mini = x;
                x->parent = NULL;
                x = pntr;
            } while (pntr != temp->child);
        }
        (temp->left)->right = temp->right;
        (temp->right)->left = temp->left;
        mini = temp->right;
        if (temp == temp->right && temp->child == NULL)
            mini = NULL;
        else
        {
            mini = temp->right;
            Consolidate();
        }
        noOfNodes--;
        return minimum;
    }
}

void Cut(Node *found, Node *temp)
{
    if (found == found->right)
        temp->child = NULL;

    (found->left)->right = found->right;
    (found->right)->left = found->left;
    if (found == temp->child)
        temp->child = found->right;

    temp->degree = temp->degree - 1;
    found->right = found;
    found->left = found;
    (mini->left)->right = found;
    found->right = mini;
    found->left = mini->left;
    mini->left = found;
    found->parent = NULL;
    found->mark = 'B';
}

void Cascase_cut(Node *temp)
{
    Node *ptr5 = temp->parent;
    if (ptr5 != NULL)
    {
        if (temp->mark == 'W')
        {
            temp->mark = 'B';
        }
        else
        {
            Cut(temp, ptr5);
            Cascase_cut(ptr5);
        }
    }
}

void Decrease_key(Node *found, int val)
{
    if (mini == NULL)
        cout << "The Heap is Empty" << endl;

    if (found == NULL)
        cout << "Node not found in the Heap" << endl;

    found->key = val;

    Node *temp = found->parent;
    if (temp != NULL && found->key < temp->key)
    {
        Cut(found, temp);
        Cascase_cut(temp);
    }
    if (found->key < mini->key)
        mini = found;
}

void Find(Node *mini, int old_val, int val)
{
    Node *found = NULL;
    Node *temp5 = mini;
    temp5->c = 'Y';
    Node *found_ptr = NULL;
    if (temp5->key == old_val)
    {
        found_ptr = temp5;
        temp5->c = 'N';
        found = found_ptr;
        Decrease_key(found, val);
    }
    if (found_ptr == NULL)
    {
        if (temp5->child != NULL)
            Find(temp5->child, old_val, val);
        if ((temp5->right)->c != 'Y')
            Find(temp5->right, old_val, val);
    }
    temp5->c = 'N';
    found = found_ptr;
}

void Deletion(int val)
{
    if (mini == NULL)
        cout << "The heap is empty" << endl;
    else
    {
        Find(mini, val, 0);
        Extract_min();
        cout << "Key Deleted" << endl;
    }
}

void display()
{
    Node *ptr = mini;
    if (ptr == NULL)
        cout << "The Heap is Empty" << endl;

    else
    {
        cout << "The root nodes of Heap are: " << endl;
        do
        {
            cout << ptr->key;
            ptr = ptr->right;
            if (ptr != mini)
            {
                cout << "-->";
            }
        } while (ptr != mini && ptr->right != NULL);
        cout << endl
             << "The heap has " << noOfNodes << " nodes" << endl
             << endl;
    }
}

int main()
{
    cout << "Creating an initial heap" << endl;
    insertion(5);
    insertion(2);
    insertion(8);
    insertion(7);
    insertion(12);
    insertion(1);
    insertion(3);
    insertion(9);
    insertion(6);

    display();

    cout << "Extracting min" << endl;
    cout << Extract_min() << endl;
    display();

    cout << "Extracting min" << endl;
    cout << Extract_min() << endl;
    display();

    cout << "Decrease value of 12 to 11" << endl;
    Find(mini, 12, 11);
    display();

    cout << "Delete the Node 7" << endl;
    Deletion(7);
    display();

    return 0;
}
