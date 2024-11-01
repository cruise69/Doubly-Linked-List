#pragma once
#include <iostream>
using namespace std;

template <class T>
class clsDblLinkedList
{
    class Node
    {
    public:
        T value;
        Node *next = NULL;
        Node *prev = NULL;

        Node(T val = T()) : value(val), next(NULL), prev(NULL){};
    };
    Node *head = new Node();
    unsigned long long _size = 0;
    void RefreshCycle() // Refresh cycle between head node and last node
    {
        if (head->next == NULL)
            return;
        Node *temp = GetLastNode();
        head->prev = temp;
        temp->next = head;
    }
    void RefreshPrevs() // Refresh nodes prev pointer
    {
        if (head->next == NULL)
            return;
        Node *temp = head;
        while (temp->next != head && temp->next != NULL)
        {
            temp->next->prev = temp;
            temp = temp->next;
        }
    }

public:
    Node *GetFirstNode()
    {
        return head->next;
    }
    Node *GetLastNode()
    {
        Node *temp;
        temp = head;
        while (temp->next != head && temp->next != nullptr)
        {
            temp = temp->next;
        }
        if (temp->next == head || temp->next == NULL)
        {
            return temp;
        }
        delete temp;
        return NULL;
    }
    void DeleteFirstNode()
    {
        Node *toDelete = head->next;
        Node *toModify = toDelete->next;
        if (toModify != nullptr)
        {
            toModify->next = toDelete->next;
        }
        toModify->prev = toDelete->prev;
        head->next = toModify;
        delete toDelete;
        toDelete = nullptr;
        RefreshCycle();
        RefreshPrevs();
        _size--;
    }
    void DeleteLastNode()
    {
        Node *toDelete = GetLastNode();
        Node *toModify = toDelete->prev;
        if (toModify != nullptr)
        {
            toModify->next = toDelete->next;
        }
        toModify->next = toDelete->next;
        head->prev = toModify;
        delete toDelete;
        toDelete = nullptr;
        RefreshCycle();
        RefreshPrevs();
        _size--;
    }
    void DeleteNode(T value)
    {
        Node *toDelete = Find(value);
        Node *toModify = toDelete->prev;
        if (toModify != nullptr)
        {
            toModify->next = toDelete->next;
        }
        delete toDelete;
        toDelete = nullptr;
        RefreshCycle();
        RefreshPrevs();
        _size--;
    }
    Node *Find(T value)
    {
        Node *temp = head;
        while (temp->next != NULL)
        {
            if (temp->value == value)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }
    void InsertAtTheBegining(T value)
    {
        Node *tempNode = new Node();
        tempNode->value = value;
        tempNode->next = head->next;
        head->next = tempNode;
        tempNode->prev = head;
        RefreshPrevs();
        RefreshCycle();
        _size++;
    }
    void InsertAtTheEnd(T value)
    {
        Node *temp = new Node();
        temp->value = value;
        temp->next = NULL;
        GetLastNode()->next = temp;
        temp->prev = GetLastNode();
        RefreshPrevs();
        RefreshCycle();
        _size++;
    }
    void InsertAfter(T prevNodeValue, T afterNodeValue)
    {
        Node *prevNode = Find(prevNodeValue);
        Node *afterNode = new Node();
        afterNode->value = afterNodeValue;
        afterNode->next = prevNode->next;
        afterNode->prev = prevNode;
        prevNode->next = afterNode;
        RefreshPrevs();
        RefreshCycle();
        _size++;
    }
    int Size() { return _size; }
    bool IsEmpty() { return _size == 0; }
    void Clear()
    {
        if (_size == 0 || head->next == NULL)
            return;
        Node *temp = head->next;
        while (temp->next != NULL && temp->next != head)
        {
            temp = temp->next;
            delete temp->prev;
        }
        delete temp->next;
        delete temp;
        head->next = NULL;
        head->prev = NULL;
        _size = 0;
        RefreshCycle();
        RefreshPrevs();
    }
    void Reverse()
    {
        Node *temp = GetLastNode();
        Node *temp2 = GetLastNode();
        head->next = temp;
        while (temp->prev != head->next && temp->prev != NULL)
        {
            temp->next = temp->prev;
            temp->prev = temp2->next;
            temp = temp->next;
            temp2 = temp2->prev;
        }
        RefreshCycle();
        RefreshPrevs();
    }
    Node *GetNode(unsigned long long Index)
    {
        Node *temp = head;
        Node *empty = new Node();
        empty->value = -1;
        if (Index > _size)
            return empty;
        for (unsigned long long i = 0; i < Index; i++)
        {
            temp = temp->next;
        }
        delete empty;
        return temp;
    }
    T GetItem(unsigned long long Index) { return GetNode(Index)->value; };
    void UpdateItem(T value, unsigned long long Index) { GetNode(Index)->value = value; }
    void InsertAfter(unsigned long long Index, T value, short variation)
    {
        if (Index > _size)
            return;
        Node *prevNode = GetNode(Index);
        Node *afterNode = new Node();
        afterNode->value = value;
        afterNode->next = prevNode->next;
        afterNode->prev = prevNode;
        prevNode->next = afterNode;
        RefreshPrevs();
        RefreshCycle();
        _size++;
    }
    void ListNodes()
    {
        if (_size == 0)
        {
            cout << "None to Print";
            return;
        }
        Node *temp = head;
        while (temp->next != head && temp->next != NULL)
        {
            temp = temp->next;
            cout << temp->value << endl;
        }
    }
};