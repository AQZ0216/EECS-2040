#include <iostream>

using namespace std;

class Node;

class LinkedList
{
public:
    LinkedList();
    void insertBack(string stop);
    void insertStop(string src, string dst, string newStop, string method);
    void deleteStop(string stop);
    void Reverse();
    void print();
private:
    Node* first;
    Node* last;
};

class Node
{
friend LinkedList;
public:
    Node(string element, Node* next);
private:
    string data;
    Node* link;
};

int main()
{
    int n;
    string s;
    string operation;

    LinkedList* route = new LinkedList();
    route->insertBack("NTHU");
    route->insertBack("TSMC");
    route->insertBack("NTHU");

    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> operation;

        if(operation == "INSERT")
        {
            string src;
            string dst;
            string newStop;
            string method;

            cin >> src;
            cin >> dst;
            cin >> newStop;
            cin >> method;

            route->insertStop(src, dst, newStop, method);
        }
        else if(operation == "DELETE")
        {
            string stop;
            cin >> stop;
            route->deleteStop(stop);
        }
        else if(operation == "REVERSE")
        {
            route->Reverse();
        }
    }

    route->print();

    return 0;
}

LinkedList::LinkedList()
{
    first = 0;
    last = 0;
}

void LinkedList::insertBack(string stop)
{
    if(first)
    {
        last->link = new Node(stop, 0);
        last = last->link;
    }
    else
    {
        first = new Node(stop, 0);
        last = first;
    }
}

void LinkedList::insertStop(string src, string dst, string newStop, string method)
{
    Node *next;
    for(Node* curr = first; curr != 0; curr = next)
    {
        next = curr->link;
        if(curr->data == src && next != 0 && next->data == dst)
        {
            curr->link = new Node(newStop, next);
        }
    }

    if(method == "2")
    {
        for(Node* curr = first; curr != 0; curr = curr->link)
        {
            next = curr->link;
            if(curr->data == dst && next != 0 && next->data == src)
            {
                curr->link = new Node(newStop, next);
            }
        }
    }

    return;
}

void LinkedList::deleteStop(string stop)
{
    Node *next;
    for(Node* curr = first; curr != 0; curr = next)
    {
        next = curr->link;
        if(next != 0 && next->data == stop)
        {
            curr->link = next->link;
            delete next;
        }

        next = curr->link;
        while((curr->link) != 0 && (curr->link)->data == curr->data)
        {
            curr->link = next->link;
            delete next;
        }
    }

    return;
}

void LinkedList::Reverse()
{
    Node *curr = first;
    Node *prev = 0;
    Node *r = 0;

    while(curr)
    {
        r = prev;
        prev = curr;
        curr = curr->link;
        prev->link = r;
    }
    first = prev;
}

void LinkedList::print()
{
    for(Node* ptr = first; ptr != 0; ptr = ptr->link)
    {
        if(ptr != first)
        {
           cout << "->";
        }

        cout << ptr->data;
    }
    cout << endl;
}


Node::Node(string element, Node* next)
{
    data = element;
    link = next;
}
