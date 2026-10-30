// Alternative: one Parcel structure with optional fields, and a function template
#include <iostream>
#include <cmath>
#include <type_traits>

constexpr long long RATE_PER_KG_PAISE = 5000, EXPRESS_PAISE = 4000;
constexpr int INSURANCE_PERCENT = 2;

struct Parcel {                                   // all options named at the call site
    double kg;
    bool express = false;
    bool insured = false;
    bool fragile = false;                         // NEW option: one added line, no caller changes
};

long long charge(const Parcel& p)
{
    long long base = std::llround(p.kg * RATE_PER_KG_PAISE);
    long long total = base;
    if (p.express) total += EXPRESS_PAISE;
    if (p.insured) total += (base * INSURANCE_PERCENT + 50) / 100;
    if (p.fragile) total += 1500;
    return total;
}

template <typename W>                              // template: any weight type, resolved at compile time
long long chargeT(W weight)
{
    if constexpr (std::is_integral_v<W>) return weight * RATE_PER_KG_PAISE / 1000;   // grams
    else return std::llround(weight * RATE_PER_KG_PAISE);                           // kg
}

int main()
{
    std::cout << charge(Parcel{2.5}) << ' ' << charge(Parcel{2.5, true}) << ' '
              << charge(Parcel{2.5, true, true}) << ' ' << charge(Parcel{2.5, false, false, true}) << '\n';
    std::cout << chargeT(2500) << ' ' << chargeT(2.5) << ' ' << chargeT(2.5f) << '\n';
    std::cout << "sizeof(Parcel) = " << sizeof(Parcel) << " bytes (copied if passed by value)\n";
}
