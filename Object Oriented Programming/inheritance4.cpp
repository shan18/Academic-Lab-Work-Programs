# include <iostream>
using namespace std;

class A {
public:
	A() {
		cout << "Constructor A" << endl;
	}
};

class B {
public:
	B() {
		cout << "Constructor B" << endl;
	}
};

class C : public A, B {
public:
	C() : B(), A() {
		cout << "Constructor C" << endl;
	}
};

int main() {
	C c;
}
