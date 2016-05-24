#include <iostream>
#include "LLRBT.h"
#include "LLRBT.cpp"

using namespace std;

int main() {
	LLRBT<int>* test = new LLRBT<int>();
	test->insert(1);
	test->insert(0);
	test->insert(2);
	cout << test->contains(1) << "\n";
	cout << test->contains(0) << "\n";
	cout << test->contains(-1) << "\n";
	delete test;
	return 0;
}
