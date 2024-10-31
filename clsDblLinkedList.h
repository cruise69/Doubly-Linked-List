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
    }
    void ListNodes()
    {
        Node *temp = head;
        while (temp->next != head && temp->next != NULL)
        {
            temp = temp->next;
            cout << temp->value << endl;
        }
    }
};