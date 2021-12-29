#include <iostream>
#include "stack.h"
#include "time.h"


int main()
{
    srand(time(NULL));
    for (int j = 150; j <= 1500; j += 150) {
        Stack s;
        for (int i = 0; i < j; i++)
            s.push(rand() % 100);
        //        s.print();
        unsigned int time1 = clock();
        qsortHoare(s, 0, s.size);
        unsigned int time2 = clock();
        //        s.print();
        std::cout << "Number of elements : " << j << " Time : " << time2 - time1 << ", N_op = " << s.N_op << std::endl;
    }
    return 0;
}
