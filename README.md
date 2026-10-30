# DSA01-<RegisterNumber>-Assignment2

**Name:** Myyuri  **Register number:** <RegisterNumber>
**Compiler:** g++ (Ubuntu 13.3.0) 13.3.0
**Compile command:** `g++ -std=c++17 -Wall -Wextra <file>.cpp -o <name>` (timing programs also with `-O0` / `-O2` as stated in the report)
**Run:** `./<name>`

| Folder | Programs | Result |
|---|---|---|
| Q1 | `predict.cpp`, `complete_code.cpp`, `three_ways.cpp`, `copy_cost.cpp` | Prediction `1 12 13 / 1 100 / 16 13 6`; by value leaves 45000, by reference/pointer give 40500 |
| Q2 | `marks_register.cpp`, `dangling.cpp`, `vector_growth.cpp`, `vector_use_after_free.cpp`, `alt_index_pointer.cpp` | Reference moderates the array; dangling reference warned; vector reallocation moves the buffer |
| Q3 | `ambiguous.cpp`, `courier.cpp`, `long_ambiguity.cpp`, `alt_parcel_template.cpp` | Ambiguity explained; redesigned overloads select as predicted |
| Q4 | `savings_account.cpp`, `history_benchmark.cpp` | Last 10 transactions kept; shifting vs circular vs deque timed |
| Q5 | `predict.cpp`, `complete_code.cpp`, `bus_ticket_design.cpp`, `function_twice.cpp`, `ticket_office.cpp` | `101 103 104 4`; seats 1-3 then waiting list |
| Q6 | `complete_code.cpp`, `time_tests.cpp`, `inline_benchmark.cpp` | `205 false`; 6/6 tests; inline timings at -O0 and -O2 |
| Q7 | `compare.cpp` | Circular buffer: identical output, 18.9x faster at K=500 |

Output screenshots: add your own terminal screenshots to each folder (`*_output.txt` and `*_compile.txt` hold the captured text).
