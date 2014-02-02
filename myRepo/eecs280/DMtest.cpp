#include <iostream>

int main()
{
    int *p = new int(100);
    int *q = p;
    delete q; q=0;
    std::cout << *p << std::endl;
    return 0;
}
