/*
  Node* getLinkedList()--create a simple linked list and return a pointer to its head node.
  Node* reverseLinkedList(Node *head)--reverse a linked list which starts with node "*head".
  void deleteLinkedList(Node *head)--delete the linked list which starts with node "*head".
*/
#include<iostream>

using namespace std;

class Node {
public:
	int value;
	Node *next;


	Node() 
	{
		value = 0;
		next = nullptr;
	};
	Node(int v);
	Node(int v, Node *n);
};

Node::Node(int v)
{
	value = v;
	next = nullptr;
}

Node::Node(int v, Node *n)
{
	value = v;
	next = n;
}

Node* getLinkedList()
{
	Node *head;
	head = new Node(0);
	Node *currentNode = head;

	for (int i = 1; i <= 9; i++)
	{
		currentNode->next = new Node(i);
		currentNode = currentNode->next;
	}
	

	return head;
}

Node * reverseLinkedList(Node * head)
{
	if (head == nullptr)
		return head;
	if (head->next == nullptr)
		return head;
	Node *pCurrent,*pFront;
	Node currentNode;
	pCurrent = head;
	pFront = nullptr;
	currentNode = *pCurrent;
	pCurrent->next = pFront;


	while (currentNode.next!= nullptr)
	{
		pFront = pCurrent;
		pCurrent = currentNode.next;

		currentNode = *pCurrent;
		pCurrent->next = pFront;
	}

	head = pCurrent;
	return head;
	
}

void deleteLinkedList(Node *head)
{
	if (head->next != nullptr)
	{
		deleteLinkedList(head->next);
	}
	cout << "Node " << head->value << " was deleted." << endl;
	delete head;
	head = nullptr;
}

int main()
{
	Node *head = getLinkedList();
	Node *np = head;
	do {
		cout << np->value << '\n';
		np = np->next;
	} while (np->next!=nullptr);
	cout << np->value << endl;

	cout << "After reversal:\n";
	head = reverseLinkedList(head);
	np = head;
	do {
		cout << np->value << '\n';
		np = np->next;
	} while (np->next != nullptr);
	cout << np->value << endl;

	deleteLinkedList(head);

	return 0;
}
