// Cost of passing a large Student by value, by reference and by const reference
#include <chrono>
#include <iostream>

struct Student { char name[256]; int marks[64]; long long fee; };   // large object

__attribute__((noinline)) long long byValue(Student s)             { return s.fee + s.marks[3]; }
__attribute__((noinline)) long long byRef(Student& s)              { return s.fee + s.marks[3]; }
__attribute__((noinline)) long long byConstRef(const Student& s)   { return s.fee + s.marks[3]; }
__attribute__((noinline)) long long smallByValue(long long fee)    { return fee + 1; }

int main()
{
    std::cout << "sizeof(long long) = " << sizeof(long long) << " bytes, sizeof(Student) = "
              << sizeof(Student) << " bytes, sizeof(reference/pointer) = " << sizeof(void*) << " bytes\n";
    Student s{};
    s.fee = 45000; s.marks[3] = 7;
    const long long N = 20000000;
    long long sink = 0;
    using ms = std::chrono::duration<double, std::milli>;
    auto t0 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) { s.marks[3] = static_cast<int>(i & 63); sink += byValue(s); }
    auto t1 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) { s.marks[3] = static_cast<int>(i & 63); sink += byRef(s); }
    auto t2 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) { s.marks[3] = static_cast<int>(i & 63); sink += byConstRef(s); }
    auto t3 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) sink += smallByValue(i);
    auto t4 = std::chrono::steady_clock::now();
    std::cout << N << " calls:  Student by value " << ms(t1 - t0).count() << " ms,  by reference "
              << ms(t2 - t1).count() << " ms,  by const reference " << ms(t3 - t2).count()
              << " ms,  long long by value " << ms(t4 - t3).count() << " ms\n";
    std::cout << "(checksum " << sink << ")\n";
}
