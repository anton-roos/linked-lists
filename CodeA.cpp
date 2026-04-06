#include<iostream>
using namespace std;

struct node
{
	int data;
	node *next;	
};

class singlelist
{
//class with the functions to handle the nodes
//2 constructors:  head and tail
	private:
		node * head, * tail;
	public:
		singlelist()
		{
			//initialised as NULL to avoid junk data
			head = NULL;  
			tail = NULL;  
		}

	void createNode(int nodevalue)
	//function to create nodes with
	{
		node *temp = new node;
		temp -> data = nodevalue;
		temp -> next = NULL;
		if (head==NULL)
		{
			head=temp;
			tail=temp;
			temp=NULL;
		}
		else
		{
			tail-> next=temp;
			tail=temp;
		}
	}//createNode

	void insert_head(int nodevalue)
	//function to insert node at the start of the list
	//same function for inserting node at the end
	{
		node *temp = new node;
		temp -> data = nodevalue;
		temp -> next = head;
		head = temp;
	}//insert_head

	void insert_position(int pos, int nodevalue)
	//function to insert a node at a specific position in the list
	{
		node *previous = new node;
		node *current = new node;
		node *temp = new node;
		current = head;
		for (int i = 1; i < pos; i++){
			previous=current;
			current=current -> next;
		}//for
		temp -> data = nodevalue;
		previous -> next = temp;
		temp -> next = current;
	}//insert_position

	void delete_head()
	//function to remove the first node (head)
	{
		node *temp=new node;
		temp=head;
		head = head -> next;
		delete temp;
	}//delete_head

	void delete_tail()
	//function to remove the tail - remember you need to know the node before the last before you can delete the last
	{
		node *current=new node;
 		node *previous=new node;
    		current=head;
    		while(current->next!=NULL)
		{
			previous=current;
			current=current->next;	
		}
	    	tail=previous;
    		previous->next=NULL;
    		delete current;
	}//delete_tail

	void remove_position(int pos)
	//function to remove node at a specific position
	{
		node *current=new node;
    		node *previous=new node;
    		current=head;
    		for(int i=1;i<pos;i++)
    		{
      			previous=current;
      			current=current->next;
    		}
    		previous->next=current->next;
	}//remove_position

	void displayList()
	//code to display the nodes of the linked list
	{
		node *temp=new node;
		temp=head;
		while(temp!=NULL)
		{
			cout <<temp -> data <<"\t";
			temp=temp -> next;	
		}
	}//displayList
};