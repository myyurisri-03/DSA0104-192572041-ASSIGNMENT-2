// 10,000,000 calls: friend vs member vs getters, each with inline and forced non-inline
#include <chrono>
#include <iostream>
#include <vector>
#define NOINL __attribute__((noinline))

class Time {
    int h, m;
public:
    Time(int hh = 0, int mm = 0) : h(hh), m(mm) {}
    int hours() const { return h; }                        // getters (defined in class = inline)
    int minutes() const { return m; }
    NOINL int hoursN() const { return h; }
    NOINL int minutesN() const { return m; }
    int minutesTo(const Time& o) const { int x = h*60+m, y = o.h*60+o.m; return x > y ? x - y : y - x; }   // member
    NOINL int minutesToN(const Time& o) const { int x = h*60+m, y = o.h*60+o.m; return x > y ? x - y : y - x; }
    friend inline int minutesBetween(const Time& a, const Time& b);                                         // friend
    friend NOINL int minutesBetweenN(const Time& a, const Time& b);
};
inline int minutesBetween(const Time& a, const Time& b) { int x = a.h*60+a.m, y = b.h*60+b.m; return x > y ? x - y : y - x; }
NOINL int minutesBetweenN(const Time& a, const Time& b) { int x = a.h*60+a.m, y = b.h*60+b.m; return x > y ? x - y : y - x; }
inline int viaGetters(const Time& a, const Time& b) { int x = a.hours()*60+a.minutes(), y = b.hours()*60+b.minutes(); return x > y ? x - y : y - x; }
NOINL int viaGettersN(const Time& a, const Time& b) { int x = a.hoursN()*60+a.minutesN(), y = b.hoursN()*60+b.minutesN(); return x > y ? x - y : y - x; }

template <typename F> double timeIt(const std::vector<Time>& v, long long N, F f)
{
    long long sink = 0; size_t n = v.size();
    auto t0 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) sink += f(v[i & (n - 1)], v[(i * 7 + 3) & (n - 1)]);   // n = 1024, so & is a cheap modulo
    auto t1 = std::chrono::steady_clock::now();
    if (sink == -1) std::cout << "x";
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}
int main()
{
    std::vector<Time> v;
    for (int i = 0; i < 1024; ++i) v.emplace_back((i * 5) % 24, (i * 13) % 60);
    const long long N = 10000000;
    std::cout << N << " calls, times in ms\n";
    std::cout << "friend  inline     : " << timeIt(v, N, [](const Time& a, const Time& b){ return minutesBetween(a, b); }) << '\n';
    std::cout << "friend  not inline : " << timeIt(v, N, [](const Time& a, const Time& b){ return minutesBetweenN(a, b); }) << '\n';
    std::cout << "member  inline     : " << timeIt(v, N, [](const Time& a, const Time& b){ return a.minutesTo(b); }) << '\n';
    std::cout << "member  not inline : " << timeIt(v, N, [](const Time& a, const Time& b){ return a.minutesToN(b); }) << '\n';
    std::cout << "getters inline     : " << timeIt(v, N, [](const Time& a, const Time& b){ return viaGetters(a, b); }) << '\n';
    std::cout << "getters not inline : " << timeIt(v, N, [](const Time& a, const Time& b){ return viaGettersN(a, b); }) << '\n';
}
