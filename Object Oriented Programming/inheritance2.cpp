#include <iostream>
using namespace std;

class triangle {
protected:
	int A,B,C;
public:
	triangle(): A(0), B(0), C(0)
		{ }
	triangle(int a, int b, int c): A(a), B(b), C(c)
		{ }
};

class Area : public triangle {
public:
	Area() : triangle()
		{ }
	Area(int a, int b, int c): A(a), B(b), c(c)
		{ }
	void calc() {
		cout << 0.5*B*C << endl;
	}
};

class Perimeter : public triangle {
public:
	Perimeter() : triangle()
		{ }
	Perimeter(int a, int b, int c): triangle(a,b,c)
		{ }
	void calc() {
		cout << A+B+C << endl;
	}
};

int main() {
	Area S(10, 20, 30);
	Perimeter P(12, 13, 14);
	S.calc();
	P.calc();
}
