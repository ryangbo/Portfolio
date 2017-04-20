class Node
{
	public:
	char letter; //letter being stored into list
	Node *next; //location of next node
	Node *previous; //location of previous node
	Node(char input, Node * node_ptr, Node *prev_ptr); //constructor for class Node - takes input of letter and current location of node
};

class List
{
	public:
	Node *head; //head of list for letters A-Z
	Node *current; //current location of list, used for inserting letters
	Node *previous; //used to keep track of location for inserting letters
	List(); //constructor for class List
	void insertElement(char letter); //Add letter to list 
	void removeElement(char letter); //Remove letter from list
	void printList(); //print contents of list
	void searchList(char letter); //search contents for letter
	void moveLeft(); //move current pointer to the left if possible
	void moveRight();//move current pointer to the right if possible
};

//THINGS TO DO:
// -USE PRIVATE VARIBALES IN CLASS WITH GET() AND SET()