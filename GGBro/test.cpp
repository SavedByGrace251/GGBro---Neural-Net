// testing file for cpp things

#include <iostream>
using namespace std;

int call(int& n) {
	cout << "call made " << n << endl;
	n = n - 1;
	return n;
}

int main() {
	int n = 10;
	for (int i = 0; i < call(n); i++) {
	}
	return 0;
}