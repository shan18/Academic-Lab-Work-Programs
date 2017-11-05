# include <iostream>
using namespace std;

class Count {
public:
	int count;
	Count(): count(0)
		{ }
	Count(int c): count(c)
		{ }
	void operator ++() {		// postfix
		count++;
	}
	void operator ++(int);		// prefix
	void show() {
		cout << count << endl;
	}
};

void Count::operator ++(int) {
	++count;
}

Count operator +(Count a, Count b) {		// operator overloading outside the class
		int m = b.count + a.count;
		return Count(m);
}

int main() {
	Count s, t(5), u;
	s++;
	++t;
	u = s + t;
	cout << "s = ";
	s.show();
	cout << "t = ";
	t.show();
	cout << "u = ";
	u.show();
}
