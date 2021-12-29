#include "stack.h"
#include <iostream>

Stack::Stack()  //3
{
    N_op = 0; N_op++;   //1
    size = 0; N_op++;   //1
    data = nullptr; N_op++; //1
}

Stack::Stack(int in[]) {    //5
    N_op = 1;   //1
    data = in; N_op++;  //1
    size = sizeof(data) / 4; N_op += 3;   //3
}

Stack::~Stack() {
    if (size > 0)   //1
        delete[] data;  //1
    N_op++;
}

void Stack::push(int val) { //3n + 7
    if (size == 0) {    //1 + 2 + 2 = 5
        data = new int[1]; N_op += 2; //2
        data[0] = val; N_op += 2; //2
    }
    else {  //1 + 2 + 3n + 2 + 1 = 3n + 6
        int* temp = data; N_op++;  //1
        data = new int[size + 1]; N_op += 2;  //2
        for (int i = 0; i < size; i++) {    //3*n
            data[i] = temp[i]; N_op += 3; //3
        }
        data[size] = val; N_op += 2;  //2
        delete[] temp; N_op++;  //1
    }
    size++; N_op++; //1
}

int Stack::pop() {  //3n + 4
    int val;
    if (size > 1) { //1 + 3 + 2 + 3n-3 + 1 = 3n + 4
        int* temp = data; N_op++;  //1
        val = data[size - 1]; N_op += 3;  //3
        data = new int[size - 1]; N_op += 2; //2
        for (int i = 0; i < size - 1; i++) {    //3n-3
            data[i] = temp[i]; N_op += 3; //3
        }
        delete[] temp; N_op++;  //1
        size--; //1
        return val;
    }
    else {
        val = *data;
        data = nullptr;
        size--;
        return val;
    }
}

int Stack::top() {  //3
    return data[size - 1]; N_op += 3; //3
}



int Stack::at(int pos) {    // 12n^2 + 24n + 7
    Stack tmp;  //3
    int length = this->size - 1;    //3
    for (int i = 0; i < length - pos; i++) {
        tmp.push(this->pop());  //3n + 7 + 1 + 3n + 4 = 6n + 12
    }
    int result = this->pop();   //1 + *
    tmp.push(result);
    while (size > 0)
        tmp.push(this->pop());
    //summary difficulty of iterating through the list is
    // (6n + 12) * n + 1 = 6n^2 + 12n + 1
    while (tmp.size > 0)    //(6n+12) * n = 6n^2 + 12n
        this->push(tmp.pop());
    return result;
}

void Stack::set(int pos, int val) { //12n^2 + 24n + 7
    Stack tmp;  //3
    int length = this->size - 1;    //3
    for (int i = 0; i < length - pos; i++) {
        tmp.push(this->pop());  //3n + 7 + 1 + 3n + 4 = 6n + 12
    }
    tmp.push(val);  //1
    this->pop();
    while (size > 0)
        tmp.push(this->pop());
    //summary difficulty of iterating through the list is
    // (6n + 12) * n + 1 = 6n^2 + 12n + 1
    while (tmp.size > 0)    //(6n+12) * n = 6n^2 + 12n
        this->push(tmp.pop());
}
void Stack::print() {   //n + 1
    if (size == 0)  //1
        std::cout << "The stack is empty\n";
    else
        for (int i = 0; i < size; i++)  //n
            std::cout << data[i] << " ";
    std::cout << std::endl;
}

int partition(Stack& stack, int p, int r) {
    while (p != r) {
        stack.N_op++;
        while (stack.at(p) <= stack.at(r) && p != r) {
            p++; stack.N_op++;
        }
        int t = stack.at(p);
        stack.set(p, stack.at(r));
        stack.set(r, t);

        while (stack.at(p) <= stack.at(r) && p != r) {
            r--;
            stack.N_op++;
        }
        int t1 = stack.at(p);
        stack.set(p, stack.at(r));
        stack.set(r, t1);
    }
    return p;
}

void qsortHoare(Stack& stack, int p, int r) {
    if (p < r) {
        stack.N_op++;
        int q = partition(stack, p, r);

        qsortHoare(stack, p, q - 1);

        qsortHoare(stack, q + 1, r);
    }
}
