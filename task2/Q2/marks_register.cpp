#include <iostream>

int& highest(int* marks, int n)                 // returns a reference INTO the array
{
    int best = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[best]) best = i;
    return marks[best];
}
const int& highestConst(const int* marks, int n) // read-only reference
{
    int best = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[best]) best = i;
    return marks[best];
}
int highestCopy(const int* marks, int n)         // returns a copy
{
    return highestConst(marks, n);
}

void print(const char* label, const int* m, int n)
{
    std::cout << label;
    for (int i = 0; i < n; ++i) std::cout << ' ' << m[i];
    std::cout << '\n';
}

int main()
{
    int marks[] = {56, 78, 91, 64, 88};
    const int n = 5;
    print("original      :", marks, n);

    highest(marks, n) += 2;                     // moderation applied directly to the element
    print("after += 2    :", marks, n);

    highest(marks, n) = 95;                     // the call on the left of =
    print("after = 95    :", marks, n);

    int copy = highestCopy(marks, n);           // a copy: changing it does not touch the array
    copy += 5;
    print("copy changed  :", marks, n);
    std::cout << "copy = " << copy << '\n';

    int& r = highest(marks, n);                 // a reference variable bound to the element
    r = 90;
    print("through r     :", marks, n);

    const int& cr = highestConst(marks, n);
    // cr = 1;                                  // ERROR: assignment of read-only reference
    std::cout << "const reference reads " << cr << '\n';
}
