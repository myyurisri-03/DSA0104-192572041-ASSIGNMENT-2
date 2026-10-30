// A reference into a std::vector becomes invalid when the vector reallocates
#include <iostream>
#include <vector>
int main()
{
    std::vector<int> marks{56, 78, 91, 64, 88};
    marks.shrink_to_fit();
    int& top = marks[2];                          // reference to 91
    const int* before = &marks[0];
    std::cout << "capacity before = " << marks.capacity() << ", address of element 0 = " << static_cast<const void*>(before) << '\n';
    marks.push_back(70);                          // size exceeds capacity -> reallocation
    const int* after = &marks[0];
    std::cout << "capacity after  = " << marks.capacity() << ", address of element 0 = " << static_cast<const void*>(after) << '\n';
    std::cout << "buffer moved: " << std::boolalpha << (before != after) << '\n';
    std::cout << "top still refers to the OLD buffer: " << (&top != &marks[2]) << '\n';
    // std::cout << top;   // undefined behaviour: reading freed memory
}
