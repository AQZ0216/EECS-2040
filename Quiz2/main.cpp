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
    void rename(string oldName, string newName);
    int distance(string src, string dst);
    void Reverse();
    void print();
    int sum();
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
	else if(operation == "RENAME")
	{
	    string oldName;
	    string newName;

	    cin >> oldName;
	    cin >> newName;

	    route->rename(oldName, newName);
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

    cout << "Total " << (route->sum())-1 << endl;

    cin >> n;
    for(int i = 0; i < n; i++)
    {
	string src;
	string dst;

	cin >> src;
	cin >> dst;

	int length = route->distance(src, dst);

	cout << src << " " << dst << " ";
	if(length >= 0)
	{
	    cout << length << endl;
	}
	else if(length == -1)
	{
	    cout << "Missing src" << endl;
	}
	else if(length == -2)
        {
            cout << "Missing dst" << endl;
        }
	else if(length == -3)
        {
            cout << "Missing both" << endl;
        }
    }
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
        while(next != 0 && next->data == curr->data)
        {
            curr->link = next->link;
            delete next;
        }
    }

    return;
}

void LinkedList::rename(string oldName, string newName)
{
    for(Node* curr = first; curr != 0; curr = curr->link)
    {
        if(curr->data == oldName)
        {
            curr->data = newName;
        }
    }

    return;
}

int LinkedList::distance(string src, string dst)
{
    int srcDistance1 = -1;
    int srcDistance2 = -1;
    int dstDistance1 = -1;
    int dstDistance2 = -1;
    int i = 0;
    for(Node* curr = first; curr != 0; curr = curr->link)
    {
        if(curr->data == src)
        {
            if(srcDistance1 >= 0)
            {
                srcDistance2 = i;
                break;
            }
                srcDistance1 = i;
        }
        i++;
    }

    i = 0;
    for(Node* curr = first; curr != 0; curr = curr->link)
    {
        if(curr->data == dst)
        {
            if(dstDistance1 >= 0)
            {
                dstDistance2 = i;
                break;
            }
                dstDistance1 = i;
        }
        i++;
    }

    if(srcDistance1 == -1 && dstDistance1 == -1)
        return -3;
    else if(srcDistance1 == -1)
        return -1;
    else if(dstDistance1 == -1)
        return -2;

    int min = -1;
    int length = sum();
    if( (min == -1 || dstDistance1-srcDistance1 < min) && dstDistance1-srcDistance1 >= 0 && srcDistance1 != -1)
        min = dstDistance1-srcDistance1;
	if( (min == -1 || dstDistance1-srcDistance2 < min) && dstDistance1-srcDistance2 >= 0 && srcDistance2 != -1)
        min = dstDistance1-srcDistance2;
	if( (min == -1 || dstDistance2-srcDistance1 < min) && dstDistance2-srcDistance1 >= 0 && srcDistance1 != -1)
	    min = dstDistance2-srcDistance1;
	if( (min == -1 || dstDistance2-srcDistance2 < min) && dstDistance2-srcDistance2 >= 0 && srcDistance2 != -1)
	    min = dstDistance2-srcDistance2;
    if( (min == -1 || length+dstDistance1-srcDistance1 < min) && dstDistance1 != -1)
	    min = length+dstDistance1-srcDistance1-1;
    if( (min == -1 || length+dstDistance1-srcDistance2 < min) && dstDistance1 != -1)
	    min = length+dstDistance1-srcDistance2-1;
    if( (min == -1 || length+dstDistance2-srcDistance1 < min) && dstDistance2 != -1)
	    min = length+dstDistance2-srcDistance1-1;
    if( (min == -1 || length+dstDistance2-srcDistance2 < min) && dstDistance2 != -1)
	    min = length+dstDistance2-srcDistance2-1;
    return min;
}

void LinkedList::Reverse()
{
    Node *curr = first;
    Node *prev = 0;
    Node *r = 0;

    last = first;

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

int LinkedList::sum()
{
    int i = 0;
    for(Node* curr = first; curr != 0; curr = curr->link)
    {
        i++;
    }

    return i;
}

Node::Node(string element, Node* next)
{
    data = element;
    link = next;
}
