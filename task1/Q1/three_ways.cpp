// Hostel fee concession: by value, by reference, by pointer, and by returned value
#include <algorithm>
#include <array>
#include <iostream>
#include <string>

constexpr int MERIT = 10, SPORTS = 15, SINGLE_PARENT = 25;     // percent

void byValue(long long fee, int percent)                       // a copy
{
    fee -= fee * percent / 100;
    std::cout << "  inside byValue the local fee is " << fee << '\n';
}
void byReference(long long& fee, int percent)
{
    fee -= fee * percent / 100;
}
void byPointer(long long* fee, int percent)
{
    if (fee != nullptr)                                        // guard against nullptr
        *fee -= *fee * percent / 100;
}
long long reduced(long long fee, int percent)     // returns the new fee
{
    return fee - fee * percent / 100;
}

struct Student { std::string name; long long fee; };
void printReceipt(const Student& s)                            // read-only: const reference
{
    std::cout << s.name << " pays " << s.fee << '\n';
}

int main()
{
    long long f1 = 45000, f2 = 45000, f3 = 45000;
    byValue(f1, MERIT);
    byReference(f2, MERIT);
    byPointer(&f3, MERIT);
    std::cout << "stored fee after byValue     : " << f1 << '\n';
    std::cout << "stored fee after byReference : " << f2 << '\n';
    std::cout << "stored fee after byPointer   : " << f3 << '\n';

    std::cout << "\nSeveral concessions (merit 10, sports 15, single parent 25) on 45000,\n"
                 "applied by returned value in every possible order:\n";
    std::array<int, 3> p{MERIT, SPORTS, SINGLE_PARENT};
    std::sort(p.begin(), p.end());
    do {
        long long fee = 45000;
        for (int pct : p) fee = reduced(fee, pct);
        std::cout << "  " << p[0] << "%, " << p[1] << "%, " << p[2] << "%  -> " << fee << '\n';
    } while (std::next_permutation(p.begin(), p.end()));

    Student s{"Asha", 45000};
    printReceipt(s);
}
