#include <iostream>
using namespace std;
int minLength(int target, int nums[], int n) {
    int left = 0, sum = 0, minLength = n + 1;
    for (int right = 0; right < n; right++) { // Duyet qua cac phan tu trong mang bang bien "right" va tinh tong
        sum += nums[right];
        while (sum >= target) { // Neu vuot qua "target" cap nhat lai do dai cua mang con ngan nhat "minLength"
            minLength = (right - left + 1 < minLength) ? (right - left + 1) : minLength;
            sum -= nums[left];
            left++;
        }
    }
    return (minLength == n + 1) ? 0 : minLength; // Neu "minLength" khong doi tra ve 0 nguoc lai tra ve "minLenght"
}
int main() {
    int arr[100], n, target;
    cin >> target;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << minLength(target, arr, n);
    return 0;
}