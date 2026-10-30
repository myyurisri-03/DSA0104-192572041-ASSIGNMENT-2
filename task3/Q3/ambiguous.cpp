// The developer's version: does not compile
#include <iostream>
double charge(double weight)                        { return weight * 50; }
double charge(double weight, bool express)          { return weight * 50 + (express ? 40 : 0); }
double charge(double weight, bool express = false, bool insured = false)
{
    return weight * 50 + (express ? 40 : 0) + (insured ? 10 : 0);
}
int main()
{
    std::cout << charge(2.0) << '\n';               // 1-arg: overload 1 or overload 3?
    std::cout << charge(2.0, true) << '\n';         // 2-arg: overload 2 or overload 3?
}
