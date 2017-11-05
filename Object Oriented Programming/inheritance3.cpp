#include <iostream>
using namespace std;

class triangle {
protected:
	int A,B,C;
public:
	triangle(int a, int b, int c) {
		A = a;
		B = b;
		C = c;
	}
};

class Perimeter : public triangle {
public:
	Perimeter(int a, int b, int c): triangle(a, b, c) {
		cout << A+B+C << endl;
	}
};

int main() {
	Perimeter P(12, 13, 14);
}
