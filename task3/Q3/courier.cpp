// Redesigned courier charge: default arguments for options, overloads for kinds of input
#include <iostream>
#include <cmath>

constexpr long long RATE_PER_KG_PAISE   = 5000;     // Rs 50 per kg
constexpr long long EXPRESS_PAISE       = 4000;     // Rs 40 flat
constexpr int       INSURANCE_PERCENT   = 2;        // of the base charge

struct Parcel { int grams; bool express; bool insured; };

long long finish(long long base, bool express, bool insured)
{
    long long total = base;
    if (express) total += EXPRESS_PAISE;
    if (insured) total += (base * INSURANCE_PERCENT + 50) / 100;
    return total;
}

// (A) weight in grams, int: exact match for integer arguments
long long charge(int grams)
{
    std::cout << "  -> charge(int grams)              ";
    return finish(grams * RATE_PER_KG_PAISE / 1000, false, false);
}
// (B) weight in kg, double, with optional extras (defaults given from the right)
long long charge(double kg, bool express = false, bool insured = false)
{
    std::cout << "  -> charge(double kg, express, insured) ";
    return finish(std::llround(kg * RATE_PER_KG_PAISE), express, insured);
}
// (C) a Parcel object
long long charge(const Parcel& p)
{
    std::cout << "  -> charge(const Parcel&)          ";
    return finish(p.grams * RATE_PER_KG_PAISE / 1000, p.express, p.insured);
}

int main()
{
    std::cout << "charge(2)\n";                     std::cout << charge(2) << '\n';
    std::cout << "charge(2.0f)\n";                  std::cout << charge(2.0f) << '\n';
    std::cout << "charge(2.5)\n";                   std::cout << charge(2.5) << '\n';
    std::cout << "charge(2.5, true)\n";             std::cout << charge(2.5, true) << '\n';
    std::cout << "charge(2.5, true, true)\n";
    std::cout << charge(2.5, true, true) << '\n';
    std::cout << "charge(Parcel{2500, true, false})\n";
    std::cout << charge(Parcel{2500, true, false}) << '\n';
}
