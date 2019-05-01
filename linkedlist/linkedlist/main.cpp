#include "main.h"



bool searchForValue(LinkedList *l, string lastName);
void clearList(LinkedList *l);
Student GenerateStudent(vector<string> &firstNamesVector, vector<string> &lastNamesVector, vector<string> &addressesVector);
bool loadDataFiles(vector<string> &firstNamesVector, vector<string> &lastNamesVector, vector<string> &addressesVector);
bool ValueInRange(const string& input, int& min, int& max);
void printStudentInformation(Student s);
void listAllLastNames(LinkedList *l);
int mainMenu();

int main()
{
	LinkedList *l = new LinkedList();
	vector<string> firstNamesVector;
	vector<string> lastNamesVector;
	vector<string> addressesVector;
	int choice = 0;

	loadDataFiles(firstNamesVector, lastNamesVector, addressesVector);

	Student s;


	for (int i = 0; i < 200; i++)
	{
		s = GenerateStudent(firstNamesVector, lastNamesVector, addressesVector);
		l->push(s);
	}
	cout << "Welcome to the super awesome Student Registry.\n";
	cout << "Choose from the following:\n\n";
	while (true)
	{
		choice = mainMenu();
		if (choice == 5)
		{
			clearList(l);
			delete l;
			return 0;
		}
		else if (choice == 1)
		{
			// Display all students
		}
		else if (choice == 2)
		{
			// Add a student
		}
		else if (choice == 3)
		{
			// Remove a student
		}
		else if (choice == 4)
		{
			string lastName = "";
			cout << "Enter a Last Name to search for: ";
			cin >> lastName;
			cout << endl;
			if (searchForValue(l, lastName))
			{
				printStudentInformation(l->GetSearchedStudent());
			}
		}
	}
}

int mainMenu()
{
	int min = 0;
	int max = 6;
	string choice = "";
	cout << "1. Display All Students\n";
	cout << "2. Add a Student\n";
	cout << "3. Remove a Student\n";
	cout << "4. Search for a Student\n";
	cout << "5. Exit\n";
	cout << "Please enter your choice (1-5): ";
	cin >> choice;
	while (!(ValueInRange(choice, min, max)))
	{
		cout << "Error. Please enter a valid input: ";
		cin >> choice;
		cin.ignore(80, '\n');
	}
	cout << endl;
	return stoi(choice);
}

void printStudentInformation(Student s)
{
	cout << "First Name: " << s.firstName << endl;
	cout << "Last Name: " << s.lastName << endl;
	cout << "Age: " << s.age << endl;
	cout << "Date of Birth: " << s.birthDate << endl;
	cout << "Sex: " << s.sex << endl;
	cout << "Home Address: " << s.homeAddress << endl;
	cout << "Parent Phone Number: " << s.phoneNumber << endl;
	cout << "Grade: " << s.grade << endl;
	cout << "GPA: " << s.GPA << endl;
	cout << endl;
}

bool loadDataFiles(vector<string> &firstNamesVector, vector<string> &lastNamesVector, vector<string> &addressesVector)
{
	ifstream firstNames;
	ifstream lastNames;
	ifstream addresses;
	string line;
	firstNames.open("firstnames.txt");
	if (!firstNames.is_open())
	{
		cout << "Failed to open first names file." << endl;
		return false;
	}
	lastNames.open("lastnames.txt");
	if (!lastNames.is_open())
	{
		cout << "Failed to open last names file." << endl;
		return false;
	}
	addresses.open("addresses.txt");
	if (!addresses.is_open())
	{
		cout << "Failed to open address file." << endl;
		return false;
	}
	while (getline(firstNames, line))
	{
		firstNamesVector.push_back(line);
	}
	firstNames.close();
	while (getline(lastNames, line))
	{
		lastNamesVector.push_back(line);
	}
	lastNames.close();
	while (getline(addresses, line))
	{
		addressesVector.push_back(line);
	}
	addresses.close();
	return true;
}

Student GenerateStudent(vector<string> &firstNamesVector, vector<string> &lastNamesVector, vector<string> &addressesVector)
{
	Student s;
	int randFirst = rand() % 200;
	int randLast = rand() % 200;
	int randAddress = rand() % 200;
	int randAge = rand() % 5 + 14;
	float randGPA = (4 * ((float)rand() / RAND_MAX));

	s.firstName = firstNamesVector[randFirst];
	s.lastName = lastNamesVector[randLast];
	s.homeAddress = addressesVector[randAddress];
	s.age = randAge;
	s.GPA = randGPA;
	if (s.age == 14) s.grade = "Freshman";
	else if (s.age == 15)
	{
		int r = rand() % 1;
		if (r == 0) s.grade = "Freshman";
		else s.grade = "Sophomore";
	}
	else if (s.age == 16)
	{
		int r = rand() % 1;
		if (r == 0) s.grade = "Sophomore";
		else s.grade = "Junior";
	}
	else if (s.age == 17)
	{
		int r = rand() % 1;
		if (r == 0) s.grade = "Junior";
		else s.grade = "Senior";
	}
	else s.grade = "Senior";

	int r = rand() % 1;
	if (r == 0) s.sex = "Male";
	else s.sex = "Female";
	long long longr = rand() % 6058929999 + 6055690000;
	s.phoneNumber = longr;
	s.birthDate = "March 4, 2005";
	

	return s;
}

bool searchForValue(LinkedList *l, string lastName)
{
	if (l->search(lastName))
	{
		cout << "Student: " << lastName.c_str() << " found!" << endl;
		cout << endl;
		return true;
	}
	else
	{
		cout << "Student: " << lastName.c_str() << " not found!" << endl;
		cout << endl;
		return false;
	}

}

void clearList(LinkedList *l)
{
	while (!l->IsEmpty())
	{
		if (l->pop())
		{
			Student s = l->GetPoppedValue();
			cout << "Removed node from list!" << endl;
			printStudentInformation(s);
		}
		else cout << "Failed to remove node from list!" << endl;
		cout << "Length of list is: " << l->GetLength() << endl;
	}
}

bool ValueInRange(const string& input, int& min, int& max)
{
	if (!input.empty() && find_if(input.begin(), input.end(), [](char c) { return !std::isdigit(c); }) == input.end())
	{
		int value = atoi(input.c_str());
		return (value < max && value > min);
	}
	return false;
}

void listAllLastNames(LinkedList *l)
{

}
