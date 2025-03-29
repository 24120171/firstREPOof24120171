#include <iostream>
using namespace std;
int sentinelLinearSearch(int a[], int n, int k) {
	int last = a[n - 1]; // Store the last element
	a[n - 1] = k; // Set the sentinel
	int i = 0;
	while (a[i] != k) {
		i++;
	}
	a[n - 1] = last; // Restore the last element
	// If found within original range, return index; otherwise, return -1
	if (i < n - 1 || a[n - 1] == k)
		return i;
	return -1;
}
int main() {
	int n, k;
	int arr[100];
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cin >> k;
	cout << sentinelLinearSearch(arr, n, k);
	return 0;
}