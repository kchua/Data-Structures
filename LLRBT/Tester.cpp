#include <iostream>
#include "LLRBT.h"
#include "LLRBT.cpp"

using namespace std;

int main() {
	LLRBT<int>* test = new LLRBT<int>();
	test->insert(0);
	test->insert(1);
	test->insert(4);
	test->insert(3);
	test->insert(2);
	cout << test->contains(1) << "\n";
	cout << test->contains(0) << "\n";
	cout << test->contains(4) << "\n";
	cout << test->contains(3) << "\n";
	cout << test->contains(2) << "\n";
	cout << test->contains(-1) << "\n\n";
	test->clear();
	cout << test->contains(1) << "\n";
	cout << test->contains(0) << "\n";
	cout << test->contains(4) << "\n";
	cout << test->contains(3) << "\n";
	cout << test->contains(2) << "\n";
	cout << test->contains(-1) << "\n\n";
	delete test;
}
