#include <iostream>
using namespace std;
bool canShip(int weights[], int n, int days, int capacity) { // Xet tinh kha thi cua viec cho hang trong n ngay voi khoi luong "capacity"
    int total = 0, day_count = 1; // Khoi tao so ngay toi thieu la 1
    for (int i = 0; i < n; i++) {
        if (total + weights[i] > capacity) { // Neu tong khoi luong vuot qua "capacity" tang "day_count" tra tong "total" ve 0
            day_count++;
            total = 0;
        }
        total += weights[i]; // Bat dau tinh khoi luong hang cho ngay tiep theo
    }
    return day_count <= days; 
}
int shipWithinDays(int weights[], int n, int days) {
    int left = weights[0], right = 0;
    for (int i = 0; i < n; i++) {  // Tim gia tri lon nhat và tong trong luong
        if (weights[i] > left) left = weights[i];
        right += weights[i];
    }

    while (left < right) { // Dung Binary Search tim "mid" la so ngay có kha nang thoa yeu cau
        int mid = left + (right - left) / 2;
        if (canShip(weights, n, days, mid)) {
            right = mid; // Neu ham "canShip" tra ve "true" giam tai trong
        }
        else {
            left = mid + 1; // Neu tra ve "false" tang tai trong
        }
    }
    return left; 
}
int main() {
    int arr[100], n, days;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> days;
    cout << shipWithinDays(arr, n, days) << endl;
	return 0;
}