#pragma once
#include <string>

using namespace std;

class Student
{
public:
	Student(int studentID_in, string studentName_in, string studentAddress_in, string studentPhone_in);
	~Student();
	
	int getID();
	string getName();
	string getAddress();
	string getPhone();
	bool operator < (Student s) const;

	int studentID;
	string studentName;
	string studentAddress;
	string studentPhone;
};
