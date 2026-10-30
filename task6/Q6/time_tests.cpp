// Correctness tests for the friend functions (times on the same day; no overnight wrap)
#include <iomanip>
#include <iostream>
class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};
int minutesBetween(const Time& a, const Time& b)
{
    int ma = a.h * 60 + a.m, mb = b.h * 60 + b.m;
    return ma > mb ? ma - mb : mb - ma;
}
bool earlier(const Time& a, const Time& b) { return a.h < b.h || (a.h == b.h && a.m < b.m); }

struct Case { const char* name; Time a, b; int diff; bool earlierAB; };
int main()
{
    const Case cases[] = {
        {"9:45 -> 13:10 (given)",        {9, 45},  {13, 10}, 205, true},
        {"same time twice 10:30",        {10, 30}, {10, 30}, 0,   false},
        {"before / after noon 11:50-12:20", {11, 50}, {12, 20}, 30, true},
        {"exactly noon vs 11:59",        {12, 0},  {11, 59}, 1,   false},
        {"midnight vs 23:59",            {0, 0},   {23, 59}, 1439, true},
        {"order reversed 13:10 vs 9:45", {13, 10}, {9, 45},  205, false},
    };
    int pass = 0, total = 0;
    std::cout << std::left << std::setw(34) << "Case" << std::setw(16) << "diff exp/act" << std::setw(18) << "earlier(a,b) e/a" << "Result\n";
    for (const Case& c : cases) {
        int d = minutesBetween(c.a, c.b); bool e = earlier(c.a, c.b);
        bool ok = d == c.diff && e == c.earlierAB; ++total; pass += ok;
        std::cout << std::setw(34) << c.name << std::setw(16) << (std::to_string(c.diff) + "/" + std::to_string(d))
                  << std::setw(18) << (std::string(c.earlierAB ? "true" : "false") + "/" + (e ? "true" : "false")) << (ok ? "PASS" : "FAIL") << '\n';
    }
    std::cout << pass << " / " << total << " passed\n";
}
