// Same program, but reads the stale reference. Compile with -fsanitize=address to see it caught.
#include <iostream>
#include <vector>
int main()
{
    std::vector<int> marks{56, 78, 91, 64, 88};
    marks.shrink_to_fit();
    int& top = marks[2];
    marks.push_back(70);
    std::cout << top << '\n';                     // stale reference
}
