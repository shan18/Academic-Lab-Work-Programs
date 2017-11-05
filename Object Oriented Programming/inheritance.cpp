#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
	string name;
	int age;
public:
	Person()
		{ }
	Person(string n, int a): name(n), age(a)
		{ }
};

class Student : public Person {
protected:
	int roll;
	string branch, college;
public:
	Student(): Person()
		{ }
	Student(string n, int a, int r, string b, string c): Person(n, a) {
		roll = r;
		branch = b;
		college = c;
	}
};

class Exam : public Student {
	int marks1, marks2;
public:
	Exam() : Student()
		{ }
	Exam(string n, int a, int r, string b, string c, int m1, int m2): Student(n, a, r, b, c) {
		marks1 = m1;
		marks2 = m2;
	}
	void total() {
		cout << "Total = " << marks1+marks2 << endl;
	}
	void examDetails() {
		cout << "Name: " << name << endl << "Age: " << age << endl;
		cout << "Roll: " << roll << endl << "Branch: " << branch << endl << "college: " << college << endl;
		cout << "Marks 1: " << marks1 << endl << "Marks 2: " << marks2 << endl;
		total();
	}
};

int main() {
	Exam E("Shantanu Acharya", 20, 150023, "Computer Science and Engineering", "Harvard University", 98, 100);
	E.examDetails();
}
