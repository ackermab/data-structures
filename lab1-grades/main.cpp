#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "student.h"
#include "grade.h"

using namespace std;

int readStudent(char *filename, vector<Student>& students)
{
	ifstream fin;
	fin.open(filename);

	int id;
	string name;
	string address;
	string phone;

	while(fin >> id)
	{
		fin.ignore(1000, '\n');
		getline(fin,name);
		getline(fin,address);
		getline(fin,phone);

		Student newStudent(id, name, address, phone);
		students.push_back(newStudent);

	}
	
	return 0;
}

int readGrade(char *filename, vector<Grade>& grades)
{
	ifstream fin;
	fin.open(filename);

	int id;
	string className;
	string grade;

	while(fin >> className)
	{
		fin >> id;
		fin >> grade;

		Grade newGrade(id, className, grade);
		grades.push_back(newGrade);

	}
	return 0;
}

int printStudents(ofstream& fout, vector<Student>& students)
{
	

	int n = students.size();

	for (int i = 0; i < n; i++)
	{
		fout << students[i].getName() << endl;
		fout << students[i].getID() << endl;
		fout << students[i].getPhone() << endl;
		fout << students[i].getAddress() << endl;
	}	

	return 0;
}

int printGrades(ofstream& fout, vector<Grade>& grades)
{

	int m = grades.size();

	for (int j = 0; j < m; j++)
	{
		fout << grades[j].getID() << "\t";
		fout << grades[j].getGrade() << "\t";
		fout << grades[j].getClass() << endl;
	}
	return 0;
}

void query(char *filename, ofstream& fout, vector<Student>& students, vector<Grade>& grades)
{
	ifstream fin;
	fin.open(filename);
cout << "test1" << endl;
	int id;
	while (fin >> id)
	{
		double points = 0;
		int numClasses = 0;

		int n = grades.size();
		for(int i = 0; i < n; i++)
			if (grades[i].getID() == id)
			{
				points = grades[i].gradeToInt() + points;
				numClasses++;
			}

		double gpa = 0;

		if (numClasses != 0)
			gpa = points / (double)numClasses;

		bool studentFound = false;
		int m = students.size();
		int j;
		for(j = 0; j < m; j++)
			if (students[j].getID() == id)
			{
				studentFound = true;
				cout << "Found " << id << " at " << j << endl;
				break;
			}

		if (studentFound == true)
			fout << id << "\t" << fixed << setprecision(2) << setfill('0') << gpa << "\t" << students[j].getName() << endl;
	}
}

int main(int argc, char *argv[])
{
	vector<Student> students;
	vector<Grade> grades;

	readStudent(argv[1], students);
	readGrade(argv[2], grades);

	sort(students.begin(), students.end());
	sort(grades.begin(), grades.end());

	ofstream fout;
	fout.open(argv[4]);

	if (students.size() > 0)
		printStudents(fout, students);	

	fout << endl;

	if (grades.size() > 0)
		printGrades(fout, grades);

	if (students.size() > 0)
	{
		fout << endl;
		query(argv[3], fout, students, grades);
	}

	return 0;
}
