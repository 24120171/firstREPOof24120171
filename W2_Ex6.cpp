#include <iostream>
using namespace std;
bool YorN(int arr[], int n, int target) {
	int left = 0, right = n - 1, sum; // Khoi tao 2 bien trai phai la phan tu dau va cuoi cua mang
	for (left; left < right; ) {
		sum = arr[right] + arr[left]; // Tinh "sum" bang tong dau va cuoi 
		if (sum == target) {
			return true;
		}
		if (sum > target) { // Neu sum > target dich bien phai ve ben trai nguoc lai neu sum < target
			right--;
		}
		else {
			left++;
		}
	}
	return false;
}
int main() {
	int arr[100], n, target;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cin >> target;
	if (YorN(arr, n, target)) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
	return 0;
}