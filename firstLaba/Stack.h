#ifndef STACK_H
#define STACK_H


class Stack
{
private:
    int* data;
public:
    int size;
    unsigned long long N_op;

    Stack();
    Stack(int in[]);
    ~Stack();

    void push(int val);
    int pop();
    int top();
    int at(int pos);
    void set(int pos, int val);
    void print();
};

int partition(Stack& s, int p, int r);
void qsortHoare(Stack& s, int p, int r);

#endif // STACK_H
