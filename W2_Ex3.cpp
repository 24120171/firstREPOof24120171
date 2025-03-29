#include <iostream>
using namespace std;
int findMin(int arr[], int n) {
	int left = 0, right = n - 1;

	while (left < right) {
		int mid = left + (right - left) / 2;

		if (arr[mid] > arr[right]) {
			left = mid + 1;  // Gia tri nho nhat phai o nua ben phai
		}
		else {
			right = mid;  // Gia tri nho nhat phai nam o ben trai hoac chinh no
		}
	}

	return arr[left];  // Gia tri nho nhat
}
int main() {
	int arr[100], n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
		cout << findMin(arr, n);
	return 0;
}
	