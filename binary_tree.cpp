#include<iostream>
#include<vector>;
#include<queue>;
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

// Tạo giá trị cho key và gán các giá trị còn lại là NULL.
NODE* createNode(int data) {
	NODE* node = new NODE;
	node->key = data;
	node->p_left = NULL;
	node->p_right = NULL;
	return node;
}

// Sử dụng 1 hàm phụ để duyệt qua các NODE từ trái qua phải bằng cách gọi đệ quy
void NLR_phu(NODE* pRoot, vector<int>& array) {
	if (pRoot == NULL) return;
	array.push_back(pRoot->key);
	NLR_phu(pRoot->p_left, array);
	NLR_phu(pRoot->p_right, array);
}
vector<int> NLR(NODE* pRoot) {
	vector<int> array;
	NLR_phu(pRoot, array);
	return array;
}

// Tương tự cách hoạt động của hàm NLR
void LNR_phu(NODE* pRoot, vector<int>& array) {
	if (pRoot == NULL) return;
	LNR_phu(pRoot->p_left, array);
	array.push_back(pRoot->key);
	LNR_phu(pRoot->p_right, array);
}
vector<int> LNR(NODE* pRoot) {
	vector<int> array;
	LNR_phu(pRoot, array);
	return array;
}

// Tương tự cách hoạt động của hàm NLR
void LRN_phu(NODE* pRoot, vector<int>& array) {
	if (pRoot == NULL) return;
	LRN_phu(pRoot->p_left, array);
	LRN_phu(pRoot->p_right, array);
	array.push_back(pRoot->key);
}
vector<int> LRN(NODE* pRoot) {
	vector<int> array;
	LRN_phu(pRoot, array);
	return array;
}

// Tạo 1 queue làm hàng đợi duyệt qua hết từng NODE trong queue và thêm vào level. 
// Duyệt từng NODE có con không và thêm vào Queue cho lần duyệt tiếp theo.
vector<vector<int>> LevelOrder(NODE* pRoot) {
	vector<vector<int>> result;
	if (!pRoot) return result;

	queue<NODE*> q;
	q.push(pRoot);

	while (!q.empty()) {
		int n = q.size();
		vector<int> level;
		for (int i = 0; i < n; i++) {
			NODE* node = q.front(); q.pop();
			level.push_back(node->key);
			if (node->p_left != NULL) q.push(node->p_left);
			if (node->p_right != NULL) q.push(node->p_right);
		}
		result.push_back(level);
	}
	return result;
}

// Sử dụng đệ quy cộng 1 cho đến khi hết cây
int countNode(NODE* pRoot) {
	if (pRoot == NULL) return 0;
	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// Cách hoạt động tương tự hàm countNode, cộng dồn cho đến hết cây bằng đệ quy
int sumNode(NODE* pRoot) {
	if (pRoot == NULL) return 0;
	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

// Dùng 2 hàm phụ: 1 hàm tính chiều cao và 1 hàm tìm value.
// Hàm tính chiều cao: dùng đệ quy tính số cạnh về 2 phía của NODE kết quả là số lớn hơn.
// Hàm tìm value: tham khảo cách hoạt động đệ quy từ chatGPT.
int height(NODE* node) {
	if (node == NULL) return -1;
	int leftHeight = height(node->p_left);
	int rightHeight = height(node->p_right);
	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

NODE* findNode(NODE* pRoot, int value) {
	if (pRoot == NULL) return NULL;
	if (pRoot->key == value) return pRoot;
	NODE* leftResult = findNode(pRoot->p_left, value);
	if (leftResult) return leftResult;
	return findNode(pRoot->p_right, value);
}

int heightNode(NODE* pRoot, int value) {
	NODE* target = findNode(pRoot, value);
	if (target == NULL) return -1;
	return height(target);
}

// Sử dụng đệ quy duyệt qua từng tầng của cây cho đến khi tìm được p.
int Level(NODE* pRoot, NODE* p) {
	if (!pRoot) return -1;
	if (pRoot == p) return 0;

	int left = Level(pRoot->p_left, p);
	if (left != -1) return left + 1;

	int right = Level(pRoot->p_right, p);
	if (right != -1) return right + 1;

	return -1;
}

// Đệ quy cho đến khi NODE đang xét là NODE lá và cộng 1 ngược về.
int countLeaf(NODE* pRoot) {
	if (!pRoot) return 0;
	if (!pRoot->p_left && !pRoot->p_right) return 1;
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}