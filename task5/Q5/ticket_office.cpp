// Alternative: seat counter kept in a TicketOffice object instead of a static member
#include <iostream>
#include <string>
class TicketOffice {
    int issued = 0; int capacity;
public:
    explicit TicketOffice(int cap) : capacity(cap) {}
    int nextSeat() { return issued < capacity ? ++issued : 0; }
    int count() const { return issued; }
};
class BusTicket {
    int seat; std::string name;
public:
    BusTicket(const std::string& n, TicketOffice& office) : seat(office.nextSeat()), name(n) {}
    void print() const { std::cout << "  " << name << ": " << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n'; }
};
int main()
{
    TicketOffice bus1(3), bus2(2);                       // two buses at once - impossible with one static counter
    BusTicket a("Asha", bus1), b("Bala", bus1), c("Chitra", bus1), d("Dev", bus1);
    BusTicket e("Esha", bus2), f("Farid", bus2), g("Gita", bus2);
    std::cout << "Bus 1:\n"; a.print(); b.print(); c.print(); d.print();
    std::cout << "Bus 2:\n"; e.print(); f.print(); g.print();
    std::cout << "Issued bus 1 = " << bus1.count() << ", bus 2 = " << bus2.count() << '\n';
}
