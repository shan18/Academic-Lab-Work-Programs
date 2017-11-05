// Bag into which fruits can be placed
// Maximun number of items that a bag can hold

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

int main() {
 Bag bag;
 int item;
 while(true) {
 	cout << "Enter Item Number to be put into the bag <0-no item>: ";
 	cin >> item;
 	if(item == 0)	// end of an item, break
 		break;
 	bag.put(item);
 	cout << "Items in bag: ";
 	bag.show();
 	if(bag.IsFull()) {
 		cout << "Bag Full, no more items can be placed";
 	}
 }
 return 0;
}
