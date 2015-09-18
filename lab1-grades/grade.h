#pragma once
#include <string>

using namespace std;

class Grade
{
public:
	Grade(int studentID_in, string studentClass_in, string studentGrade_in);
	~Grade();

	int getID();
	string getGrade();
	string getClass();
	double gradeToInt();
	bool operator < (Grade s) const;

	string studentClass;
	int studentID;
	string studentGrade;

};
