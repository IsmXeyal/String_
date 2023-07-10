#include <iostream>
#include <cassert>

using namespace std;

#include"myString.h"

int main() {
	myString str("MyStringg");
	cout << str.print() << endl;
	cout << str.size() << endl;
	cout << str.capacity() << endl;

	myString str2("MyStringgg", " Class");
	cout << str2.print() << endl;
	cout << str2.size() << endl;
	cout << str2.capacity() << endl;

	cout << str.front() << endl;
	cout << str.back() << endl;
	cout << str.find('a') << endl;
	cout << str.rfind('g') << endl;

	str2.substr(4, 5);
	cout << str2.print() << endl;

	str.erase(4, 5);
	cout << str.print() << endl;


	return 0;
}