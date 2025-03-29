#include <iostream>
using namespace std;
int linearSearch(int arr[], int n, int k) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == k) {
			return i; // Return the index directly
		}
	}
	return -1; // Return -1 if not found
}
int main() {
	int n, k;
	int arr[100];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cin >> k;
	cout << linearSearch(arr, n, k);
	return 0;
}