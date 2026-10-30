// Highest mark returned as reference, index and pointer: calling code, time and vector safety
#include <chrono>
#include <iostream>
#include <vector>

int&  highestRef(std::vector<int>& v) { size_t b = 0; for (size_t i = 1; i < v.size(); ++i) if (v[i] > v[b]) b = i; return v[b]; }
size_t highestIndex(const std::vector<int>& v) { size_t b = 0; for (size_t i = 1; i < v.size(); ++i) if (v[i] > v[b]) b = i; return b; }
int*  highestPtr(std::vector<int>& v) { size_t b = 0; for (size_t i = 1; i < v.size(); ++i) if (v[i] > v[b]) b = i; return &v[b]; }

int main()
{
    std::vector<int> v{56, 78, 91, 64, 88};
    highestRef(v) += 2;                          // reference:  highestRef(v) += 2;
    v[highestIndex(v)] += 2;                     // index:      v[highestIndex(v)] += 2;
    *highestPtr(v) += 2;                         // pointer:    *highestPtr(v) += 2;
    std::cout << "after three moderations of +2: " << v[2] << " (expected 97)\n";

    // Safety when the container grows: keep the index and it still works
    size_t idx = highestIndex(v);
    int* p = highestPtr(v);
    v.shrink_to_fit(); idx = highestIndex(v); p = highestPtr(v);
    int* oldP = p;
    for (int i = 0; i < 100; ++i) v.push_back(1);  // forces reallocation
    std::cout << "index after growth still valid: v[idx] = " << v[idx] << '\n';
    std::cout << "pointer kept before growth is stale: " << std::boolalpha << (oldP != &v[idx]) << '\n';

    // Timing: O(n) for all three
    const size_t N = 5000000;
    std::vector<int> big(N);
    for (size_t i = 0; i < N; ++i) big[i] = static_cast<int>((i * 2654435761u) % 1000003);
    using ms = std::chrono::duration<double, std::milli>;
    long long sink = 0;
    auto t0 = std::chrono::steady_clock::now();
    for (int r = 0; r < 20; ++r) sink += highestRef(big);
    auto t1 = std::chrono::steady_clock::now();
    for (int r = 0; r < 20; ++r) sink += big[highestIndex(big)];
    auto t2 = std::chrono::steady_clock::now();
    for (int r = 0; r < 20; ++r) sink += *highestPtr(big);
    auto t3 = std::chrono::steady_clock::now();
    std::cout << "n = " << N << ", 20 searches: reference " << ms(t1 - t0).count() << " ms, index "
              << ms(t2 - t1).count() << " ms, pointer " << ms(t3 - t2).count() << " ms (checksum " << sink << ")\n";
    std::cout << "bytes returned: reference/pointer " << sizeof(int*) << ", index " << sizeof(size_t) << '\n';
}
