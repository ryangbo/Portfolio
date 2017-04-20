#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "hw4_classes.h"
#include "hw4_functions.h"

using namespace std;

//Constructor for class Node, used to locate the current letter, next, and previous nodes
Node::Node(char input, Node *node_ptr, Node *prev_ptr)
{
	letter=input;
	next=node_ptr;
	previous=prev_ptr;
}

//Constructor for class List - initialize all variables to NULL
List::List()
{
	head = NULL;
	current = NULL;
	previous = NULL;
}

//Add letter to list and alphabetize
void List::insertElement(char letter)
{
	//if head is NULL, set new letter as head and current as input letter
	if(head == NULL)
	{
		//set current and head = to the new head of list
		current = head = new Node(letter, NULL, NULL);
		cout << "Added: " << letter << endl;
	}
	else
	{
		bool inserted = false;
		current = head; //current != NULL
		previous = NULL;
		while(current != NULL && !inserted)
		{
			//check for ascii value of letter to alphabetize
			if(current->letter > letter)
			{
				//head of list, inserted letter has lesser ascii value
				if(previous == NULL)
				{
					//set new letter = to head
					head = new Node(letter, current, NULL);
					cout << "Added: " << letter << endl;
				}
				//in-between
				else
				{
					current = current->previous = previous->next = new Node(letter, current, previous); //create new node and assign pointers
					cout << "Added: " << letter << endl;
				}
				inserted = true; //break out of loop - letter has been inserted
			}
			//if duplicate
			else if(current->letter == letter)
			{
				cout << "ERROR: Duplicate of letter " << letter << endl;
				inserted = true;
			}
			//assign current to next node until NULL, or letter has been inserted
			else
			{
				previous = current;
				current = current->next; //until NULL
			}
		}
		
		//last letter
		if(!inserted)
		{
			previous->next = new Node(letter, NULL, previous);
			cout << "Added: " << letter << endl;
			current = previous->next;
		}
	}
}

void List::removeElement(char letter)
{	
	bool valid = false;
	bool deleted = false;
	
	current = head; //either NULL or != NULL
	previous = NULL;
	
	//search for letter
	while(current != NULL && !deleted)
	{
		//letter is found
		if(current->letter == letter)
		{
			//first letter, at least 2 in list
			if(current->previous == NULL && current->next != NULL)
			{
				current->next->previous = NULL; //next node's previous set to NULL
				head = current->next; //head set to next node
				delete current; //delete letter
				current = head; //cannot move left, current set to node on right
				valid = true;
			}
			//last letter
			else if(current->previous != NULL && current->next == NULL)
			{
				current->previous->next = NULL; //previous node's next set to NULL
				previous->next = current->next; //point previous to node after removal
				delete current; //delete letter
				current = previous; //current set to node on left
				valid = true;
			}
			//in between
			else if(current->previous != NULL && current->next != NULL)
			{
				current->next->previous = previous; //node after removed letter's previous set to previous node
				previous->next = current->next; //point previous to node after removal
				delete current; //delete letter
				current = previous; //set current to node on left
				valid = true;
			}
			//only one letter
			else if(current->previous == NULL && current->next == NULL)
			{
				//set pointers back to NULL
				head = NULL;
				delete current;
				current = head;
				valid = true;
			}
			deleted = true;
		}
		//iterate loop until letter is found or == NULL
		else
		{
			previous = current;
			current = previous->next;
		}
	}
	
	if(valid == true)
	{
		cout << "Removed: " << letter << endl;
	}
	else
	{
		cout << "ERROR: Not found for Removal " << letter << endl;
	}	
}

void List::printList()
{
	current = head;
	if(head == NULL)
	{
		cout << "ERROR: List is empty\n";
	}
	else
	{
		//iterate from head to NULL
		while(current != NULL)
		{
			cout << current->letter << endl;
			current = current->next;
		}
	}
	current = head;
}

void List::searchList(char letter)
{
	current = head;
	bool found = false;
	
	if(head == NULL)
	{
		cout << "ERROR: List is empty" << endl;
	}
	else
	{
		//iterate until found or current == NULL
		while(current != NULL && !found)
		{
			if(letter == current->letter)
			{
				found = true;
			}
			else
			{
				current = current->next;
			}
		}
		
		if(found == true)
		{
			cout << "TRUE: " << letter << endl;
		}
		else
		{
			cout << "FALSE: " << letter << endl;
		}
	}
}

void List::moveLeft()
{	
	if(head == NULL)
	{
		cout << "ERROR: List is empty\n";
	}
	else if(current->previous == NULL)
	{
		cout << "ERROR: Head of list\n";
	}
	else
	{
		//move left
		current = current->previous;
		cout << "Data: " << current->letter << endl;
	}
}

void List::moveRight()
{
	if(head == NULL)
	{
		cout << "ERROR: List is empty\n";
	}
	else if(current->next == NULL)
	{
		cout << "TAIL of list: Cannot move right\n";
	}
	else
	{
		//move right
		current = current->next;
		cout << "Data: " << current->letter << endl;
	}
}

//commands
void menu()
{
	cout << "Commands:\n";
	cout << "ADD\n";
	cout << "REMOVE\n";
	cout << "PRINT\n";
	cout << "LEFT\n";
	cout << "RIGHT\n";
	cout << "SEARCH\n";
	cout << "COMMANDS\n";
	cout << "EXIT\n";
}