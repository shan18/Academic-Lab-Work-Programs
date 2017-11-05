# include <iostream>
using namespace std;

const int MAX_ITEMS = 25;

class Bag {
protected:
	int contents[MAX_ITEMS];
	int ItemCount;
public:
	Bag(): ItemCount(0)
		{}
	void put(int item) {		// put an item in bag
		contents[ItemCount++] = item;
	}
	bool IsEmpty() {			// If bag is empty, 0, otherwise, 1
		return ItemCount == 0 ? true : false;
	}
	bool IsFull()				// If bag is full, 0, otherwise, 1
	{
		return ItemCount == MAX_ITEMS ? true : false;
	}
	bool IsExist(int item);
	void show();
};

// returns 1, if item is in bag, 0, otherwise
bool Bag::IsExist(int item) {
	for(int i=0; i < ItemCount; i++)
		if(contents[i] == item)
			return true;
	return false;
}

// display contents of the bag
void Bag::show() {
	for(int i=0; i < ItemCount; i++)
		cout << contents[i] << " ";
	cout << endl;
}

class Set: public Bag {
public:
	void add(int element) {
		if(!IsExist(element) && !IsFull())
			put(element);
			// element does not exist in set and it is not full
	}
	void read();
	void operator = (Set s1);
	friend Set operator + (Set s1, Set s2);
};

void Set::read() {
	int element;
	while(true) {
		cout << "Enter Set Element <0- end>: ";
		cin >> element;
		if(element ==0)
			break;
		add(element);
	}
}

void Set::operator = (Set s2) {
	for(int i=0; i< s2.ItemCount; i++)
		contents[i] = s2.contents[i];		// access Bag::contents
	ItemCount = s2.ItemCount;
}

Set operator + (Set s1, Set s2) {
	Set temp;
	temp = s1;		// copy all elements of Set s1 to temp
	// copy those elements of set s2 into temp, those do not exist in set s1
	for(int i=0; i < s2.ItemCount; i++) {
		if(!s1.IsExist(s2.contents[i]))		// if element of s2 is not in s1
			temp.add(s2.contents[i]);		// copy the unique element
	}
	return(temp);
}

int main() {
	Set s1, s2, s3;
	cout << "Enter Set 1 elements .." << endl;
	s1.read();
	cout << "Enter Set 2 elements .." << endl;
	s2.read();
	s3 = s1 + s2;
	cout << endl << "Union of s1 and s2 : ";
	s3.show();
}
