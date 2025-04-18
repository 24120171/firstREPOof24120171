#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct Stack {
	NODE* top;
};

NODE* createNode(int data){
	NODE* p = new NODE();
	p->key = data;
	p->p_next = NULL;
	return p;
}

void print(NODE* node, ofstream& fileOut) {
	if (node == NULL) return;
	print(node->p_next, fileOut);
	fileOut << node->key;
	if (node != NULL) fileOut << " ";
}

void printStack(Stack* s, ofstream& fileOut) {
	if (s->top == NULL) {
		fileOut << "EMPTY";
		return;
	}
	print(s->top, fileOut);
}

bool isEmpty(Stack s) {
	if (s.top == NULL) return true;
	return false;
}

Stack* initializeStack() {
	Stack* newStack = new Stack;
	newStack->top = NULL;
	return newStack;
}

void push(Stack& s, int key) {
	NODE* newNode = createNode(key);
	newNode->p_next = s.top;
	s.top = newNode;
	return;
}

int pop(Stack& s) {
	if (isEmpty(s)) return -999999; // cho -1 la gia tri tra ve khi stack rong
	NODE* temp = s.top;
	int value = temp->key;
	s.top = s.top->p_next;
	temp->p_next = NULL;
	delete temp;
	return value;
}

int size(Stack s) {
	NODE* counter = s.top;
	int count = 0;
	while (counter != NULL) {
		count++;
		counter = counter->p_next;
	}
	return count;
}

int main() {
	Stack* s = NULL;
	ifstream fileIn("C:\\Users\\Admin\\OneDrive\\Máy tính\\DSA\\Week5\\x64\\Debug\\input.txt");
	ofstream fileOut("C:\\Users\\Admin\\OneDrive\\Máy tính\\DSA\\Week5\\x64\\Debug\\output.txt");
	string line;
	while (getline(fileIn, line)) {
		stringstream ss(line);
		string cmd;
		ss >> cmd;
		if (cmd == "init") {
			s = initializeStack();
			printStack(s, fileOut);
			fileOut << endl;
		}
		else if (cmd == "push") {
			int value;
			ss >> value;
			push(*s, value);
			printStack(s, fileOut);
			fileOut << endl;
		}
		else if (cmd == "pop") {
			int res = pop(*s);
			if (res == -999999) {
				fileOut << "EMPTY" << endl;

			} 
			else {
				printStack(s, fileOut);
				fileOut << endl;
			}
		}
	}
	fileIn.close();
	fileOut.close();
	return 0;
}