#include "student.h"
#include <iostream>

using namespace std;

Student::Student(int studentID_in, string studentName_in, string studentAddress_in, string studentPhone_in)
{
	studentID = studentID_in;
	studentName = studentName_in;
	studentAddress = studentAddress_in;
	studentPhone = studentPhone_in;
}
Student::~Student(){}

int Student::getID()
{
	return studentID;
}

string Student::getName()
{
	return studentName;
}

string Student::getAddress()
{
	return studentAddress;
}

string Student::getPhone()
{
	return studentPhone;
}

bool Student::operator < (Student s) const {
	return studentID < s.studentID;
}
