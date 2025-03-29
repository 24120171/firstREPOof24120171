#include <iostream>
using namespace std;
void sortArray(int arr[], int n) { // Sap xep mang bang thuat toan Bubble Sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // Hoan đoi gia tri
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void findThreeSum(int arr[], int n) {
    sortArray(arr, n);
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) continue; // Bo qua so trung lap
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            if (sum == 0) {
                cout << "[" << arr[i] << "," << arr[left] << "," << arr[right] << "]";
                while (left < right && arr[left] == arr[left + 1]) left++; // Bo qua so trung lap o left
                while (left < right && arr[right] == arr[right - 1]) right--; // Bo qua so trung lap o right
                left++;
                right--;
            }
            else if (sum < 0) {
                left++; // Neu tong nho hon 0, tang left
            }
            else {
                right--; // Neu tong lon hon 0, giam right
            }
        }
    }
}
int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "[";
    findThreeSum(arr, n);
    cout << "]";
    return 0;
}