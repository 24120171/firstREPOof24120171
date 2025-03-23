#include <iostream>
using namespace std;
int factorial(int n) {
	int s = n;
	if (n <= 1) {
		return s;
	}
	s *= factorial(n - 1);
}
int main() {
	int n;
	cin >> n;
	cout << factorial(n);
	return 0;
}