#include<iostream>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};
NODE* createNode(int data) {
	NODE* node = new NODE;
	node->key = data;
	node->p_left = NULL;
	node->p_right = NULL;
	return node;
}

// Dùng đệ quy để duyệt từng NODE.
// Nếu x bằng NODE đang xét trả về NODE đó, nếu x lớn hoặc bè hơn xét lần lượt nhánh phải và trái.
NODE* Search(NODE* pRoot, int x) {
	if (pRoot == NULL) return NULL;
	if (pRoot->key == x) return pRoot;
	if (x < pRoot->key) return Search(pRoot->p_left, x);
	else return Search(pRoot->p_right, x);
}

// Nếu x bé hơn NODE chèn về phái bên trái và ngược lại.
void Insert(NODE*& pRoot, int x) {
	if (pRoot == NULL) {
		pRoot = createNode(x);
		return;
	}
	if (x < pRoot->key) Insert(pRoot->p_left, x);
	else if (x > pRoot->key) Insert(pRoot->p_right, x);
}

// Tham khảo chatGPT trường hợp NODE cần xóa có cả 2 nhánh con.
// Tìm cho đến khi gặp NODE có key = x.
// Nếu NODE chỉ có nhánh con trái hoặc phải đôn nó lên trước.
NODE* findMin(NODE* pRoot) {
    while (pRoot && pRoot->p_left) pRoot = pRoot->p_left;
    return pRoot;
}

void Remove(NODE*& pRoot, int x) {
    if (pRoot == NULL) return;
    if (x < pRoot->key) Remove(pRoot->p_left, x);
    else if (x > pRoot->key) Remove(pRoot->p_right, x);
    else {
        if (pRoot->p_left == NULL) {
            NODE* temp = pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else if (pRoot->p_right == NULL) {
            NODE* temp = pRoot->p_left;
            delete pRoot;
            pRoot = temp;
        }
        else {
            NODE* temp = findMin(pRoot->p_right); // tham khảo
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
}

// Dùng vòng lặp for chèn từng phần tử trong mảng vào cây rỗng mới tạo.
NODE* createTree(int a[], int n) {
    NODE* pRoot = NULL;
    for (int i = 0; i < n; i++) {
        Insert(pRoot, a[i]);
    }
    return pRoot;
}

// Đệ quy hàm xóa về 2 nhánh cho đến NODE lá.
void removeTree(NODE*& pRoot) {
    if (pRoot == NULL) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

// Sử dụng lại hàm ở binary_tree
int Height(NODE* pRoot) {
    if (pRoot == NULL) return -1;
    int leftHeight = Height(pRoot->p_left);
    int rightHeight = Height(pRoot->p_right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Dùng đệ quy tìm đến vị trí nhỏ hơn x.
// Đệ quy 1 lần nữa để tính tổng số NODE nhỏ hơn x.
int countLess(NODE* pRoot, int x) {
    if (pRoot == NULL) return 0;
    if (pRoot->key >= x) return countLess(pRoot->p_left, x);
    return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
}

// Tương tự hàm trên
int countGreater(NODE* pRoot, int x) {
    if (pRoot == NULL) return 0;
    if (pRoot->key <= x) return countGreater(pRoot->p_right, x);
    return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
}

// Dùng đệ quy kiểm tra đảm bảo các NODE con bên r=trái luôn nhỏ hơn NODE cha và NODE con bên phải lớn hơn NODE cha.
bool isBST(NODE* pRoot) {
    if (pRoot == NULL) return true;
    if (pRoot->key < pRoot->p_left->key || pRoot->key < pRoot->p_right->key) return false;
    return isBST(pRoot->p_left) && isBST(pRoot->p_right);
}

// Kiểm tra tương tự hàm trên nhưng thay vì sao sánh ta kiểm tra sự tồn tại của cả 2 NODE con.
bool isFullBST(NODE* pRoot) {
    if (pRoot == NULL) return true;
    if ((pRoot->p_left == NULL && pRoot->p_right) || (pRoot->p_left && pRoot->p_right == NULL)) return false;
    return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
}