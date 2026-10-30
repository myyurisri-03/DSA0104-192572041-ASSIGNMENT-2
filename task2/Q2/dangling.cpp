// Returns a reference to a local variable - compile with -Wall -Wextra to see the warning
#include <iostream>
int& broken()
{
    int local = 42;
    return local;            // 'local' is destroyed when broken() returns
}
int main()
{
    int& r = broken();       // r refers to dead storage: using it is undefined behaviour
    std::cout << "never rely on this value: " << r << '\n';
}
