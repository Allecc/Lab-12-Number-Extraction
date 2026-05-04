# Lab 12: Extracting double-precision numbers from strings (Optional)

**Course:** Software Engineering (University of Kansas)  
**Due:** Sun May 10, 2026 11:59pm  
**Submission:** Public GitHub repository URL

## Program Description
This C++ program reads strings from the user and extracts a single valid double-precision floating-point number embedded in arbitrary "garbage" characters (letters, symbols, whitespace, etc.). It strictly follows all parsing rules, valid/invalid patterns, scientific notation handling, sign rules, and edge cases specified in the lab.

- **No library string-to-number conversions** (`std::stod`, `atof`, `strtod`, etc.) are used.
- Parsing is implemented via custom character-by-character state machine.
- Input loop continues until the user types exactly `END` (case-sensitive).
- Output matches the required format exactly (`Extracted number: ####.####` with 4 decimal places via `std::fixed` + `std::setprecision(4)`, or the exact invalid message).

### How to Build and Run
```bash
g++ -std=c++17 -o lab12 lab12.cpp
./lab12