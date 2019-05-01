#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct Student
{
	string firstName;
	string lastName;
	string sex;
	string homeAddress;
	string birthDate;
	string grade;
	int age;
	long long phoneNumber;
	float GPA;
};


class LinkedList
{
	struct Node
	{
		Node *nextNode = nullptr;
		Student student;
	};
	Node *headptr;

	int length;
	Student poppedStudent;
	Student searchedStudent;

	public:
		LinkedList();
		~LinkedList();

		int GetLength();

		bool IsEmpty();
		bool push(Student s);
		bool pop();
		bool search(string lastName);

		Student GetPoppedValue();
		Student GetSearchedStudent();
};



#endif