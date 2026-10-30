// Student-derived design: class-wide data is static; array of 6 tickets for 3 seats
#include <iostream>
#include <string>

class BusTicket {
    static int issued;                       // seats given out (one copy per class)
    static int waiting;                      // waiting-list length (one copy)
    static constexpr int CAPACITY = 3;       // fixed seats             (one copy, constant)
    int seat;                                // 0 = waiting
    int waitNo;                              // position on the waiting list, 0 if seated
    std::string name;
public:
    explicit BusTicket(const std::string& n = "unnamed") : seat(0), waitNo(0), name(n)
    {
        if (issued < CAPACITY) seat = ++issued;
        else waitNo = ++waiting;
    }
    static int seatsIssued() { return issued; }   // static: no 'this'
    static int waitingCount() { return waiting; }
    void print() const
    {
        std::cout << "  " << name << ": ";
        if (seat) std::cout << "Seat " << seat << '\n';
        else      std::cout << "Waiting list #" << waitNo << '\n';
    }
};
int BusTicket::issued = 0;                   // definition: exactly once, outside the class
int BusTicket::waiting = 0;

int main()
{
    std::cout << "Before any ticket: issued = " << BusTicket::seatsIssued() << '\n';   // no object needed
    BusTicket t[6] = {BusTicket("A"), BusTicket("B"), BusTicket("C"),
                      BusTicket("D"), BusTicket("E"), BusTicket("F")};
    for (const BusTicket& x : t) x.print();
    std::cout << "Issued: " << BusTicket::seatsIssued() << ", waiting: " << BusTicket::waitingCount() << '\n';

    BusTicket defaults[2];                   // array created with the default argument
    defaults[0].print();
}
