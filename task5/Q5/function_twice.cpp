// Tickets created inside a function called twice: the static count survives the function
#include <iostream>
#include <string>
class BusTicket {
    static int issued;
    static const int CAPACITY = 3;
    int seat; std::string name;
public:
    explicit BusTicket(const std::string& n) : seat(0), name(n) { if (issued < CAPACITY) seat = ++issued; }
    static int count() { return issued; }
    void print() const { std::cout << "  " << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n'; }
};
int BusTicket::issued = 0;

void bookPair(const std::string& a, const std::string& b)
{
    BusTicket x(a), y(b);                    // local objects: destroyed when the function ends
    x.print(); y.print();
    std::cout << "  issued inside function: " << BusTicket::count() << '\n';
}
int main()
{
    std::cout << "call 1\n"; bookPair("Asha", "Bala");
    std::cout << "after call 1 (tickets destroyed) issued = " << BusTicket::count() << '\n';
    std::cout << "call 2\n"; bookPair("Chitra", "Dev");
    std::cout << "after call 2 issued = " << BusTicket::count() << '\n';
}
