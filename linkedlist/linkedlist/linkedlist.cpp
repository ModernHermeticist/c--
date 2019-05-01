#include "main.h"


LinkedList::LinkedList()
{
	headptr = nullptr;
	length = 0;
}

LinkedList::~LinkedList()
{
	delete headptr;
}

int LinkedList::GetLength()
{
	return length;
}

bool LinkedList::IsEmpty()
{
	if (headptr == nullptr) return true;
	else return false;
}

bool LinkedList::push(Student s)
{
	if (IsEmpty())
	{
		Node *temp = new Node;
		temp->nextNode = nullptr;
		temp->student = s;
		headptr = temp;
		length += 1;
		return true;
	}
	else
	{
		Node *temp = new Node;
		temp->nextNode = headptr->nextNode;
		temp->student = s;
		headptr->nextNode = temp;
		length += 1;
		return true;
	}
	return false;
}

bool LinkedList::pop()
{
	if (IsEmpty()) return false;
	Node *temp = headptr;
	poppedStudent = headptr->student;
	headptr = headptr->nextNode;
	delete temp;
	length -= 1;
	return true;
}

bool LinkedList::search(string lastName)
{
	Node *tempptr = headptr;

	while (tempptr != nullptr)
	{
		if (tempptr->student.lastName == lastName)
		{
			searchedStudent = tempptr->student;
			return true;
		}

		tempptr = tempptr->nextNode;
	}

	return false;
}

Student LinkedList::GetPoppedValue()
{
	return poppedStudent;
}

Student LinkedList::GetSearchedStudent()
{
	return searchedStudent;
}
