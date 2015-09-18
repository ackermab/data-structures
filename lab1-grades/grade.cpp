#include "grade.h"
#include <iostream>

using namespace std;

Grade::Grade(int studentID_in, string studentClass_in, string studentGrade_in)
{
	studentID = studentID_in;
	studentClass = studentClass_in;
	studentGrade = studentGrade_in;
}
Grade::~Grade(){}

int Grade::getID()
{
	return studentID;
}

string Grade::getClass()
{
	return studentClass;
}

string Grade::getGrade()
{
	return studentGrade;
}

double Grade::gradeToInt()
{
	double points;

	if (studentGrade[0] == 'A')
		points = 4.0;
	else if (studentGrade[0] == 'B')
		points = 3.0;
	else if (studentGrade[0] == 'C')
		points = 2.0;
	else if (studentGrade[0] == 'D')
		points = 1.0;
	else
		points = 0.0;

	if (studentGrade[1] == '+')
		points += .4;
	else if (studentGrade[1] == '-')
		points -= .3;
	
	return points;
}

bool Grade::operator < (Grade g) const {
	return studentID < g.studentID ||
		(studentID == g.studentID && studentClass < g.studentClass) ||
		(studentID == g.studentID && studentClass == g.studentClass && studentGrade < g.studentGrade);
}
