#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct Queue {
	NODE* head;
	NODE* tail;
};

NODE* createNode(int data) {
	NODE* p = new NODE();
	p->key = data;
	p->p_next = NULL;
	return p;
}

bool isEmpty(Queue q) {
	return q.head == NULL;
}

void printQueue(Queue& q, ofstream& fileOut) {
	if (isEmpty(q)) {
		fileOut << "EMPTY";
		return;
	}
	NODE* temp = q.head;
	while (temp != NULL) {
		fileOut << temp->key;
		if (temp->p_next != NULL) fileOut << " ";
		temp = temp->p_next;
	}
}

Queue* initializeQueue() {
	Queue* newQueue = new Queue;
	newQueue->head = NULL;
	newQueue->tail = NULL;
	return newQueue;
}

void enQueue(Queue& q, int key) {
	NODE* newNode = createNode(key);
	NODE* temp = q.head;
	if (isEmpty(q)) {
		q.head = newNode;
		q.tail = newNode;
		return;
	}
	while (temp->p_next != NULL) {
		temp = temp->p_next;
	}
	temp->p_next = newNode;
	q.tail = newNode;
}

int deQueue(Queue& q) {
	if (isEmpty(q)) return -999999;
	NODE* temp = q.head;
	int value = temp->key;
	q.head = q.head->p_next;
	if (q.head == NULL) q.tail = NULL;
	delete temp;
	return value;
}

int size(Queue& q) {
	NODE* counter = q.head;
	int count = 0;
	while (counter != NULL) {
		count++;
		counter = counter->p_next;
	}
	return count;
}

int main() {
	Queue* q = NULL;
	ifstream fileIn("C:\\Users\\Admin\\OneDrive\\Máy tính\\DSA\\Week5\\x64\\Debug\\input.txt");
	ofstream fileOut("C:\\Users\\Admin\\OneDrive\\Máy tính\\DSA\\Week5\\x64\\Debug\\output.txt");
	string line;
	while (getline(fileIn, line)) {
		stringstream ss(line);
		string cmd;
		ss >> cmd;
		if (cmd == "init") {
			q = initializeQueue();
			printQueue(*q, fileOut);
			fileOut << endl;
		}
		else if (cmd == "enqueue") {
			int value;
			ss >> value;
			enQueue(*q, value);
			printQueue(*q, fileOut);
			fileOut << endl;
		}
		else if (cmd == "dequeue") {
			int res = deQueue(*q);
			if (res == -999999) {
				fileOut << "EMPTY" << endl;

			}
			else {
				printQueue(*q, fileOut);
				fileOut << endl;
			}
		}
	}
	fileIn.close();
	fileOut.close();
	return 0;
}