#include <iostream>
#include "CodeA.cpp"
using namespace std;

class Node {
public:
    int Value;
    Node* Next;
};

static void printList(Node* n)
{
    while (n != NULL)
    {
        cout << n->Value << endl;
        n = n->Next;
    }
}

int main()
{
    Node* head = new Node();
    Node* second = new Node();
    Node* third = new Node();

    head->Value = 1;
    head->Next = second;
    second->Value = 2;
    second->Next = third;
    third->Value = 3;
    third->Next = NULL;

    printList(head);

    cout << "Single linked lists" << endl;
    singlelist list;
    //add elements to the list
    list.createNode(10);  //create the first element of the list
    list.createNode(38);
    list.createNode(88);
    list.createNode(25);
    //display the initial list of data
    list.displayList();
    cout << " " << endl;
    cout << "New Single linked lists:  66 added after 38" << endl;
    //add an element 66 after 38
    list.insert_position(3, 66); //element 38 is in position 2, thus 66 should be inserted in postion 3 
    list.displayList();
    cout << " " << endl;
    cout << "New Single linked lists:  38 removed" << endl;
    //remove element 38
    list.remove_position(2); //element 38 is in position 2
    list.displayList();
    return 0;
    
    system("pause>0");
}
