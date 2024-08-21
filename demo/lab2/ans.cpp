#include <iostream>
using namespace std;


class stack {
private:
    int *arr;
    int top;
    int capacity;
public:
    stack(int cap = 10) : top(-1), capacity(cap) {
        arr = new int[capacity];
    }
    ~stack() {
        delete[] arr;
    }
    void push(int);
    int pop();
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
    void print();
};

void stack::push(int x) {
    if (isFull()) {
        cout << "Stack is full" << endl;
        return;
    }
    arr[++top] = x;
}

class queue {
private:
    struct Node {
        int data;
        Node *next;
    };
    Node *front, *rear;
public:
    queue() : front(nullptr), rear(nullptr) {}
    ~queue() {
        while (front != nullptr) {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
    }
    void enqueue(int);
    int dequeue();
    int peek();
    int size();
    bool isEmpty();
    void print();
};


int main() {
    stack s;

}