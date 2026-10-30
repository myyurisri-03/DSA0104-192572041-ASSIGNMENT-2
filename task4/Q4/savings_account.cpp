// SavingsAccount: last 10 transactions kept in a private array (oldest discarded by shifting)
#include <iomanip>
#include <iostream>

struct Transaction { char type; long long amount; };    // 'D' deposit, 'W' withdrawal (paise)

class SavingsAccount {
    static constexpr int HISTORY = 10;                  // one constant: change it for 50
    long accountNo;
    long long balance;                                  // paise
    Transaction history[HISTORY];                       // private array
    int count;                                          // entries used (<= HISTORY)

    void record(char type, long long amount);           // private helper, defined outside
public:
    SavingsAccount(long no, long long opening)
        : accountNo(no), balance(opening), history{}, count(0) {}

    // defined INSIDE the class (implicitly inline)
    long long getBalance() const { return balance; }
    bool deposit(long long amount)
    {
        if (amount <= 0) return false;
        balance += amount;
        record('D', amount);
        return true;
    }
    // declared here, defined OUTSIDE with the scope resolution operator
    bool withdraw(long long amount);
    void miniStatement() const;
};

void SavingsAccount::record(char type, long long amount)
{
    if (count == HISTORY) {                        // 11th transaction: drop the oldest
        for (int i = 1; i < HISTORY; ++i) history[i - 1] = history[i];   // shift left: O(k)
        --count;
    }
    history[count++] = {type, amount};
}
bool SavingsAccount::withdraw(long long amount)
{
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    record('W', amount);
    return true;
}
void SavingsAccount::miniStatement() const
{
    std::cout << "Account " << accountNo << " - last " << count
              << " transactions (oldest first)\n";
    for (int i = 0; i < count; ++i)
        std::cout << "  " << std::setw(2) << i + 1 << ". "
                  << (history[i].type == 'D' ? "Deposit   " : "Withdrawal")
                  << std::setw(8) << history[i].amount << '\n';
    std::cout << "  Balance: " << balance << '\n';
}

int main()
{
    SavingsAccount acc(1001, 100000);
    for (int i = 1; i <= 12; ++i)                       // 12 transactions: 1..12
        (i % 3 == 0) ? acc.withdraw(i * 100) : acc.deposit(i * 100);
    acc.miniStatement();
    std::cout << "withdraw too much accepted? " << std::boolalpha << acc.withdraw(99999999) << '\n';
}
