// Q7: SavingsAccount history - original (shifting array) vs redesign (circular buffer)
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

struct Transaction { char type; long long amount; };

// ---------------- ORIGINAL: shift the array left when full  -> O(K) per transaction -------------
template <int K> class SavingsShift {
    long accountNo; long long balance; Transaction history[K]; int count;
    void record(char t, long long a)
    {
        if (count == K) { for (int i = 1; i < K; ++i) history[i - 1] = history[i]; --count; }
        history[count++] = {t, a};
    }
public:
    SavingsShift(long no, long long open) : accountNo(no), balance(open), history{}, count(0) {}
    bool deposit(long long a)  { if (a <= 0) return false; balance += a; record('D', a); return true; }
    bool withdraw(long long a) { if (a <= 0 || a > balance) return false; balance -= a; record('W', a); return true; }
    void miniStatement(std::ostream& os) const
    {
        os << "Account " << accountNo << " - last " << count << " transactions (oldest first)\n";
        for (int i = 0; i < count; ++i)
            os << "  " << std::setw(2) << i + 1 << ". " << (history[i].type == 'D' ? "Deposit   " : "Withdrawal") << std::setw(8) << history[i].amount << '\n';
        os << "  Balance: " << balance << '\n';
    }
};

// ---------------- REDESIGN: circular buffer with a start index -> O(1) per transaction ---------
template <int K> class SavingsCircular {
    long accountNo; long long balance; Transaction history[K];
    int start;                                     // index of the OLDEST transaction
    int count;                                     // number of valid entries
    void record(char t, long long a)
    {
        int pos = (start + count) % K;             // where the next entry goes
        history[pos] = {t, a};
        if (count < K) ++count;
        else start = (start + 1) % K;              // overwrite the oldest
    }
public:
    SavingsCircular(long no, long long open)
        : accountNo(no), balance(open), history{}, start(0), count(0) {}
    bool deposit(long long a)
    {
        if (a <= 0) return false;
        balance += a; record('D', a); return true;
    }
    bool withdraw(long long a)
    {
        if (a <= 0 || a > balance) return false;
        balance -= a; record('W', a); return true;
    }
    void miniStatement(std::ostream& os) const
    {
        os << "Account " << accountNo << " - last " << count
           << " transactions (oldest first)\n";
        for (int i = 0; i < count; ++i) {
            const Transaction& t = history[(start + i) % K];   // logical -> physical
            os << "  " << std::setw(2) << i + 1 << ". "
               << (t.type == 'D' ? "Deposit   " : "Withdrawal")
               << std::setw(8) << t.amount << '\n';
        }
        os << "  Balance: " << balance << '\n';
    }
};

template <typename Acc> std::string scenario(int n)
{
    Acc a(1001, 100000);
    for (int i = 1; i <= n; ++i) (i % 3 == 0) ? a.withdraw(i * 100) : a.deposit(i * 100);
    std::ostringstream os; a.miniStatement(os); return os.str();
}
template <int K> bool sameOutput()
{
    bool ok = true;
    for (int n : {0, 1, 5, K - 1, K, K + 1, 2 * K, 2 * K + 7, 3 * K + 3})
        ok = ok && scenario<SavingsShift<K>>(n) == scenario<SavingsCircular<K>>(n);
    return ok;
}
template <typename Acc> double nsPerDeposit(long long N)
{
    Acc a(1, 0);
    auto t0 = std::chrono::steady_clock::now();
    for (long long i = 1; i <= N; ++i) a.deposit(i % 1000 + 1);
    auto t1 = std::chrono::steady_clock::now();
    std::ostringstream os; a.miniStatement(os);                    // keep the work observable
    return std::chrono::duration<double, std::nano>(t1 - t0).count() / N + (os.str().empty() ? 1 : 0);
}
template <int K> void row(long long N)
{
    double s = nsPerDeposit<SavingsShift<K>>(N), c = nsPerDeposit<SavingsCircular<K>>(N);
    std::cout << std::setw(6) << K << std::setw(14) << std::fixed << std::setprecision(1) << s << std::setw(14) << c
              << std::setw(11) << std::setprecision(1) << s / c << "x" << std::setw(12) << sizeof(SavingsShift<K>)
              << std::setw(12) << sizeof(SavingsCircular<K>) << '\n';
}
int main()
{
    std::cout << "Same mini-statement for original and redesign (boundary counts 0,1,K-1,K,K+1,...)\n";
    std::cout << "  K = 10   : " << std::boolalpha << sameOutput<10>() << '\n';
    std::cout << "  K = 50   : " << sameOutput<50>() << '\n';
    std::cout << "  K = 500  : " << sameOutput<500>() << '\n';
    std::cout << "\nOutput of the redesign after 12 transactions (K = 10):\n" << scenario<SavingsCircular<10>>(12);
    std::cout << "\n     K  shift ns/add  circ ns/add    speed-up  bytes shift  bytes circ\n";
    const long long N = 200000;
    row<10>(N); row<50>(N); row<500>(N); row<2000>(N);
}
