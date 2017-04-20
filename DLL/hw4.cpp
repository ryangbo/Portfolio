//						 +-----------------------------------------------------------------------------------------------+
//						 |	Name: Ryan Gibeault 																		 |
//						 |	Email: Ryangibeault@my.unt.edu																 |
//						 |  Lecture section: CSCE 1040.002															     |
//						 |  Lab section: 1040.302															             |
//						 |  Date Due: 04/22/16	@ 11:59pm												 				 |
//						 |  Program Name: Homework 4																	 |
//						 |  Description: In this program, a doubly linked list is implemented to insert one character    |
//						 |  node at a time and alphabetize them. A current node pointer is used to keep track of the 	 |
//						 |  location of the current node, and functions such as add, remove, search, left, and right     |
//						 |   determine location.																		 |
//						 +-----------------------------------------------------------------------------------------------+

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "hw4_classes.h"
#include "hw4_functions.h"

using namespace std;

int main()
{	
	//Instantiation of object from List for accessing methods
	List *node_manager = new List();
	
	string choice;	//user input at command prompt
	char letter;	//input from user for adding/removing
	
	bool valid = true; //used for looping program until false
	
	cout << "---------------------------------\n";
	cout << "To Grader: Use UPPER case to access functions.\nType 'COMMANDS' for full list of commands\n";
	
	do{
		cout << "cmd> "; //command prompt on screen
		
		cin >> choice; //user input for menu options
		
		//add letter
		if(choice == "ADD") 
		{
			cin >> letter;
			node_manager->insertElement(letter);
		}
		//remove letter
		else if(choice == "REMOVE")
		{
			cin >> letter;
			node_manager->removeElement(letter);
		}
		//print list
		else if(choice == "PRINT")
		{
			node_manager->printList();
		}
		//search for letter
		else if(choice == "SEARCH")
		{
			cin >> letter;
			node_manager->searchList(letter);
		}
		//move current node pointer left
		else if(choice == "LEFT")
		{
			node_manager->moveLeft();
		}
		//move current node pointer right
		else if(choice == "RIGHT")
		{
			node_manager->moveRight();
		}
		//print list of commands
		else if(choice == "COMMANDS")
		{
			menu();
		}
		//exit program
		else if(choice == "EXIT")
		{
			valid = false;
		}
		//error message for unrecognizable commands
		else
		{
			cout << "Error: command not recognized\n";
		}
	}while(valid);
	
	cout << "GOODBYE!\n";
	
	return 0;
}