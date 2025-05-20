#include<iostream>
using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};

// Tạo giá trị cho key và gán các giá trị còn lại là NULL, 0.
NODE* createNode(int data) {
	NODE* node = new NODE;
	node->key = data;
	node->p_left = NULL;
	node->p_right = NULL;
	node->height = 0;
	return node;
}

//
