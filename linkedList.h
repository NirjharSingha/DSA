#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

class Node
{
public:
    int data;
    Node *prev;
    Node *next;

    Node()
    {
        this->prev = NULL;
        this->next = NULL;
    }

    Node(int data)
    {
        this->data = data;
        this->prev = NULL;
        this->next = NULL;
    }
};

class SinglyLinkedList
{
public:
    Node *head;
    int size;

    SinglyLinkedList()
    {
        this->head = NULL;
        size = 0;
    }

    ~SinglyLinkedList()
    {
        Node *temp = head;
        Node *temp2;

        while (temp)
        {
            temp2 = temp;
            temp = temp->next;
            delete (temp2);
        }
    }

    void insertAtBeginning(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (!head)
        {
            head = newNode;
            newNode->next = NULL;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (!head)
        {
            head = newNode;
            newNode->next = NULL;
            return;
        }

        Node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = NULL;
    }

    bool insertAtPos(int data, int pos)
    { // 0 based indexing
        if (pos < 0 || (head == NULL && pos > 0))
        {
            return false;
        }

        Node *newNode = new Node(data);
        Node *temp = head;

        if (pos == 0)
        {
            newNode->next = head;
            head = newNode;
            size++;
            return true;
        }

        for (int i = 0; i < pos - 1; i++)
        {
            if (!temp)
            {
                return false;
            }
            temp = temp->next;
        }

        if (!temp)
            return false;

        newNode->next = temp->next;
        temp->next = newNode;
        size++;
        return true;
    }

    void deleteFromBeginning()
    {
        if (head)
        {
            Node *temp = head;
            head = head->next;
            temp->next = NULL;
            delete (temp);
            size--;
        }

        if (size == 0)
        {
            head = NULL;
        }
    }

    void deleteFromEnd()
    {
        if (!head)
        {
            return;
        }

        Node *temp = head;

        if (!head->next)
        {
            head = NULL;
            size--;
            delete (temp);
            if (size == 0)
            {
                head = NULL;
            }
            return;
        }

        while (temp->next->next)
        {
            temp = temp->next;
        }

        Node *temp2 = temp->next;
        temp->next = NULL;
        size--;
        if (size == 0)
        {
            head = NULL;
        }
        delete (temp2);
    }

    bool deleteAtPos(int pos)
    { // 0 based indexing
        if (pos < 0)
        {
            return false;
        }

        if (!head)
        {
            return false;
        }

        if (pos == 0)
        {
            Node *temp = head;
            head = head->next;
            temp->next = NULL;
            delete (temp);
            size--;
            if (size == 0)
            {
                head = NULL;
            }
            return true;
        }

        Node *temp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
            if (!temp)
            {
                return false;
            }
        }

        Node *temp2 = temp->next;
        if (temp2)
        {
            temp->next = temp2->next;
            temp2->next = NULL;
            delete (temp2);
            size--;
            if (size == 0)
            {
                head = NULL;
            }
            return true;
        }

        return false;
    }

    void printList()
    {
        if (!head)
            return;
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    int dataAtIndex(int idx)
    { // 0 based indexing
        Node *temp = head;
        for (int i = 0; i < idx; i++)
        {
            if (temp)
            {
                temp = temp->next;
            }
            else
            {
                return INT_MAX;
            }
        }
        return temp->data;
    }

    int indexOfData(int data)
    { // 0 based indexing
        Node *temp = head;
        int i = 0;

        while (temp)
        {
            if (temp->data == data)
            {
                return i;
            }
            i++;
            temp = temp->next;
        }
        return -1;
    }

    bool updateAtIndex(int idx, int data)
    { // 0 based indexing
        if (!head)
        {
            return false;
        }

        Node *temp = head;
        for (int i = 0; i < idx; i++)
        {
            temp = temp->next;
            if (!temp)
            {
                return false;
            }
        }
        temp->data = data;
        return true;
    }

    int length()
    {
        return size;
    }
};

class DoublyLinkedList
{
public:
    Node *head;
    Node *tail;
    int size;

    DoublyLinkedList()
    {
        size = 0;
        this->head = NULL;
        this->tail = NULL;
    }

    ~DoublyLinkedList()
    {
        Node *temp = head;
        Node *temp2;

        while (temp)
        {
            temp2 = temp;
            temp = temp->next;
            delete (temp2);
        }
    }

    void insertAtBeginning(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (!head)
        {
            head = newNode;
            tail = newNode;
            return;
        }

        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void insertAtEnd(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (!tail)
        {
            head = newNode;
            tail = newNode;
            return;
        }

        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    bool insertAtPos(int data, int pos)
    { // 0 based indexing
        if (pos < 0 || (head == NULL && pos > 0))
        {
            return false;
        }

        Node *newNode = new Node(data);
        Node *temp = head;

        if (pos == 0)
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            size++;
            return true;
        }

        for (int i = 0; i < pos - 1; i++)
        {
            if (!temp)
            {
                return false;
            }
            temp = temp->next;
        }

        if (!temp)
            return false;

        if (temp == tail)
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            size++;
            return true;
        }

        newNode->next = temp->next;
        temp->next = newNode;
        newNode->next->prev = newNode;
        newNode->prev = temp;
        size++;
        return true;
    }

    void deleteFromBeginning()
    {
        if (head)
        {
            Node *temp = head;
            head = head->next;
            temp->next = NULL;
            if (head)
                head->prev = NULL;
            size--;
            delete (temp);
        }
        if (size == 0)
        {
            head = NULL;
            tail = NULL;
        }
    }

    void deleteFromEnd()
    {
        if (!head)
        {
            return;
        }

        if (!head->next)
        {
            Node *temp = head;
            head = NULL;
            tail = NULL;
            size--;
            if (size == 0)
            {
                head = NULL;
                tail = NULL;
            }
            delete (temp);
            return;
        }

        Node *temp = tail;
        tail = tail->prev;
        if (tail)
            tail->next = NULL;
        temp->prev = NULL;
        size--;
        if (size == 0)
        {
            head = NULL;
            tail = NULL;
        }
        delete (temp);
    }

    bool deleteAtPos(int pos)
    { // 0 based indexing
        if (pos < 0)
        {
            return false;
        }

        if (!head)
        {
            return false;
        }

        if (pos == 0)
        {
            Node *temp = head;
            head = head->next;
            temp->next = NULL;
            if (head)
                head->prev = NULL;
            delete (temp);
            size--;
            if (size == 0)
            {
                head = NULL;
                tail = NULL;
            }
            return true;
        }

        Node *temp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
            if (!temp)
            {
                return false;
            }
        }

        Node *temp2 = temp->next;
        if (temp2)
        {
            temp->next = temp2->next;
            temp->next->prev = temp;
            temp2->next = NULL;
            temp2->prev = NULL;

            if (temp2 == tail)
            {
                tail = temp;
            }

            delete (temp2);
            size--;
            if (size == 0)
            {
                head = NULL;
                tail = NULL;
            }
            return true;
        }

        return false;
    }

    void printList()
    {
        if (!head)
            return;
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void printReverse()
    {
        if (!tail)
            return;
        Node *temp = tail;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }

    int dataAtIndex(int idx)
    { // 0 based indexing
        Node *temp = head;
        for (int i = 0; i < idx; i++)
        {
            if (temp)
            {
                temp = temp->next;
            }
            else
            {
                return INT_MAX;
            }
        }
        return temp->data;
    }

    int indexOfData(int data)
    { // 0 based indexing
        Node *temp = head;
        int i = 0;

        while (temp)
        {
            if (temp->data == data)
            {
                return i;
            }
            i++;
            temp = temp->next;
        }
        return -1;
    }

    bool updateAtIndex(int idx, int data)
    { // 0 based indexing
        if (!head)
        {
            return false;
        }

        Node *temp = head;
        for (int i = 0; i < idx; i++)
        {
            temp = temp->next;
            if (!temp)
            {
                return false;
            }
        }
        temp->data = data;
        return true;
    }
    int length()
    {
        return size;
    }
};

class CircularLinkedList
{
public:
    Node *head;
    int size;

    CircularLinkedList()
    {
        this->head = NULL;
        size = 0;
    }

    ~CircularLinkedList()
    {
        if (!head)
            return;

        Node *temp = head->next;
        Node *temp2;

        while (temp != head)
        {
            temp2 = temp;
            temp = temp->next;
            delete (temp2);
        }
        delete (temp);
    }

    void insertAtBeginning(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (!head)
        {
            head = newNode;
            newNode->next = head;
            return;
        }

        Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (!head)
        {
            head = newNode;
            newNode->next = head;
            return;
        }

        Node *temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = head;
    }

    bool insertAtPos(int data, int pos)
    { // 0 based indexing
        if (pos < 0 || (pos > 0 && head == NULL))
        {
            return false;
        }

        Node *newNode = new Node(data);
        Node *temp = head;

        if (pos == 0)
        {
            while (temp->next != head)
            {
                temp = temp->next;
            }

            temp->next = newNode;
            newNode->next = head;
            head = newNode;
            size++;
            return true;
        }

        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
            if (temp == head)
            {
                return false;
            }
        }

        newNode->next = temp->next;
        temp->next = newNode;
        size++;
        return true;
    }

    void deleteFromBeginning()
    {
        if (head)
        {
            Node *temp = head;
            while (temp->next != head)
            {
                temp = temp->next;
            }

            temp->next = head->next;
            Node *temp2 = head;
            head = head->next;
            temp2->next = NULL;
            delete (temp2);
            size--;
            if (size == 0)
            {
                head = NULL;
            }
        }
    }

    void deleteFromEnd()
    {
        if (!head)
        {
            return;
        }

        Node *temp = head;

        if (head->next == head)
        {
            head = NULL;
            size--;
            if (size == 0)
            {
                head = NULL;
            }
            delete (temp);
            return;
        }

        while (temp->next->next != head)
        {
            temp = temp->next;
        }

        Node *temp2 = temp->next;
        temp->next = head;
        temp2->next = NULL;
        size--;
        if (size == 0)
        {
            head = NULL;
        }
        delete (temp2);
    }

    bool deleteAtPos(int pos)
    { // 0 based indexing
        if (pos < 0)
        {
            return false;
        }

        if (!head)
        {
            return false;
        }

        if (pos == 0)
        {
            Node *temp = head;
            Node *temp2 = head;

            while (temp->next != head)
            {
                temp = temp->next;
            }

            temp->next = head->next;
            head = head->next;
            temp2->next = NULL;
            delete (temp2);
            size--;
            if (size == 0)
            {
                head = NULL;
            }
            return true;
        }

        Node *temp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
            if (temp == head)
            {
                return false;
            }
        }

        Node *temp2 = temp->next;
        if (temp2 != head)
        {
            temp->next = temp2->next;
            temp2->next = NULL;
            delete (temp2);
            size--;
            if (size == 0)
            {
                head = NULL;
            }
            return true;
        }

        return false;
    }

    void printList()
    {
        if (!head)
            return;
        Node *temp = head;
        while (temp->next != head)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << temp->data;
        cout << endl;
    }

    int dataAtIndex(int idx)
    { // 0 based indexing
        Node *temp = head;
        for (int i = 0; i < idx; i++)
        {
            if (temp->next != head)
            {
                temp = temp->next;
            }
            else
            {
                return INT_MAX;
            }
        }
        return temp->data;
    }

    int indexOfData(int data)
    { // 0 based indexing
        Node *temp = head;
        int i = 0;

        while (temp->next != head)
        {
            if (temp->data == data)
            {
                return i;
            }

            i++;
            temp = temp->next;
        }

        if (temp->data == data)
        {
            return i;
        }

        return -1;
    }

    bool updateAtIndex(int idx, int data)
    { // 0 based indexing
        if (!head)
        {
            return false;
        }

        Node *temp = head;
        for (int i = 0; i < idx; i++)
        {
            temp = temp->next;
            if (temp == head)
            {
                return false;
            }
        }
        temp->data = data;
        return true;
    }

    int length()
    {
        return size;
    }
};

class DoublyCircularLinkedList
{
public:
    Node *head;
    int size;

    DoublyCircularLinkedList()
    {
        this->head = NULL;
        size = 0;
    }

    ~DoublyCircularLinkedList()
    {
        if (!head)
            return;

        Node *temp = head->next;
        Node *temp2;

        while (temp != head)
        {
            temp2 = temp;
            temp = temp->next;
            delete (temp2);
        }
        delete (temp);
    }

    void insertAtBeginning(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (!head)
        {
            head = newNode;
            newNode->next = head;
            newNode->prev = head;
            return;
        }

        Node *temp = head->prev;
        temp->next = newNode;
        newNode->prev = temp;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void insertAtEnd(int data)
    {
        Node *newNode = new Node(data);
        size++;

        if (!head)
        {
            head = newNode;
            newNode->next = head;
            newNode->prev = head;
            return;
        }

        Node *temp = head->prev;
        temp->next = newNode;
        newNode->prev = temp;
        newNode->next = head;
        head->prev = newNode;
    }

    bool insertAtPos(int data, int pos)
    { // 0 based indexing
        if (pos < 0 || (pos > 0 && head == NULL))
        {
            return false;
        }

        Node *newNode = new Node(data);

        if (pos == 0)
        {
            if (!head)
            {
                head = newNode;
                newNode->next = head;
                newNode->prev = head;
                size++;
                return true;
            }

            Node *temp = head->prev;
            temp->next = newNode;
            newNode->prev = temp;
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            size++;
            return true;
        }

        Node *temp = head;

        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
            if (temp == head)
            {
                return false;
            }
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        newNode->next->prev = newNode;
        temp->next = newNode;
        size++;
        return true;
    }

    void deleteFromBeginning()
    {
        if (head)
        {
            Node *temp = head->prev;
            temp->next = head->next;
            temp->next->prev = temp;
            Node *temp2 = head;
            head = head->next;
            temp2->next = NULL;
            temp2->prev = NULL;
            delete (temp2);
            size--;
        }
        if (size == 0)
        {
            head = NULL;
        }
    }

    void deleteFromEnd()
    {
        if (head)
        {
            Node *temp = head->prev->prev;
            temp->next = head;
            Node *temp2 = head->prev;
            temp->next->prev = temp;
            temp2->next = NULL;
            temp2->prev = NULL;
            delete (temp2);
            size--;
        }
        if (size == 0)
        {
            head = NULL;
        }
    }

    bool deleteAtPos(int pos)
    { // 0 based indexing
        if (pos < 0)
        {
            return false;
        }

        if (!head)
        {
            return false;
        }

        if (pos == 0)
        {
            Node *temp = head->prev;
            temp->next = head->next;
            temp->next->prev = temp;
            Node *temp2 = head;
            head = head->next;
            temp2->next = NULL;
            temp2->prev = NULL;
            delete (temp2);
            size--;
            if (size == 0)
            {
                head = NULL;
            }
            return true;
        }

        Node *temp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
            if (temp == head)
            {
                return false;
            }
        }

        Node *temp2 = temp->next;
        if (temp2 != head)
        {
            temp->next = temp2->next;
            temp->next->prev = temp;
            temp2->next = NULL;
            temp2->prev = NULL;
            delete (temp2);
            size--;
            if (size == 0)
            {
                head = NULL;
            }
            return true;
        }

        return false;
    }

    void printList()
    {
        if (!head)
            return;
        Node *temp = head;
        while (temp->next != head)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << temp->data;
        cout << endl;
    }

    void printReverse()
    {
        if (!head)
            return;
        Node *temp = head;
        while (temp->prev != head)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << temp->data;
        cout << endl;
    }

    int dataAtIndex(int idx)
    { // 0 based indexing
        Node *temp = head;
        for (int i = 0; i < idx; i++)
        {
            if (temp->next != head)
            {
                temp = temp->next;
            }
            else
            {
                return INT_MAX;
            }
        }
        return temp->data;
    }

    int indexOfData(int data)
    { // 0 based indexing
        Node *temp = head;
        int i = 0;

        while (temp->next != head)
        {
            if (temp->data == data)
            {
                return i;
            }

            i++;
            temp = temp->next;
        }

        if (temp->data == data)
        {
            return i;
        }

        return -1;
    }

    bool updateAtIndex(int idx, int data)
    { // 0 based indexing
        if (!head)
        {
            return false;
        }

        Node *temp = head;
        for (int i = 0; i < idx; i++)
        {
            temp = temp->next;
            if (temp == head)
            {
                return false;
            }
        }
        temp->data = data;
        return true;
    }

    int length()
    {
        return size;
    }
};
