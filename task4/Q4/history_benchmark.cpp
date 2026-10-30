// Cost of adding a transaction: shifting array vs circular buffer vs std::deque, for several K
#include <chrono>
#include <deque>
#include <iostream>

struct Transaction { char type; long long amount; };

template <int K> struct Shift {
    Transaction h[K]; int count = 0;
    void add(Transaction t) {
        if (count == K) { for (int i = 1; i < K; ++i) h[i - 1] = h[i]; --count; }
        h[count++] = t;
    }
    long long last() const { return h[count - 1].amount; }
};
template <int K> struct Circular {
    Transaction h[K]; int start = 0, count = 0;
    void add(Transaction t) {
        if (count < K) { h[(start + count) % K] = t; ++count; }
        else { h[start] = t; start = (start + 1) % K; }          // overwrite the oldest
    }
    long long last() const { return h[(start + count - 1) % K].amount; }
};
struct Deq {
    std::deque<Transaction> d; size_t K;
    explicit Deq(size_t k) : K(k) {}
    void add(Transaction t) { d.push_back(t); if (d.size() > K) d.pop_front(); }
    long long last() const { return d.back().amount; }
};

template <typename H> double run(H& h, long long N)
{
    long long sink = 0;
    auto t0 = std::chrono::steady_clock::now();
    for (long long i = 0; i < N; ++i) { h.add({'D', i}); sink += h.last(); }
    auto t1 = std::chrono::steady_clock::now();
    if (sink == -1) std::cout << "x";
    return std::chrono::duration<double, std::nano>(t1 - t0).count() / N;
}
template <int K> void row(long long N)
{
    Shift<K> s; Circular<K> c; Deq d(K);
    std::cout << "K = " << K << ": shifting " << run(s, N) << " ns/add, circular " << run(c, N)
              << " ns/add, deque " << run(d, N) << " ns/add, array bytes " << sizeof(s.h) << '\n';
}
int main()
{
    const long long N = 200000;
    row<10>(N); row<50>(N); row<500>(N); row<2000>(N);
}
