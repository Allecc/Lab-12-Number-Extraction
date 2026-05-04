# Lab 12: Extracting double-precision numbers from strings (Optional)

**Course:** Software Engineering (University of Kansas)  
**Due:** Sun May 10, 2026 11:59pm  
**Submission:** Public GitHub repository URL

## Program Description
This C++ program reads strings from the user and extracts a single valid double-precision floating-point number embedded in arbitrary "garbage" characters (letters, symbols, whitespace, etc.). It strictly follows all parsing rules, valid/invalid patterns, scientific notation handling, sign rules, and edge cases specified in the lab.

- No library string-to-number conversions (`std::stod`, `atof`, `strtod`, etc.) are used.
- Parsing is implemented via custom character-by-character state machine.
- Input loop continues until the user types exactly `END` (case-sensitive).
- Output matches the required format exactly (`Extracted number: ####.####` with 4 decimal places).

### How to Build and Run
```bash
g++ -std=c++17 -o lab12 lab12.cpp
./lab12

```markdown

## Documentation Requirements for GAI Code (as required by course slides)

### General Disclosure
- **GAI tool used:** Claude (specifically Claude 3.5 Sonnet)
- **Date(s) the GAI tool was consulted:** May 2, 2026 and May 3, 2026
- **Version of the tool:** Claude 3.5 Sonnet

### Code Attribution
**Exact prompts used:**

**Prompt 1 (May 2, 2026):**  
I have an optional lab in my Software Engineering class. I need to write a C++ program that reads a string and extracts ONE valid floating-point number from it while ignoring random garbage characters. I cannot use std::stod or strtod. The program must loop until the user types exactly 'END'. Please help me design a robust character-by-character parser.

**Prompt 2 (May 2, 2026):**  
My first attempt fails on cases like '+-12.34' and '12a3.45'. Also need to reject very large integers like 99999999999999999999 as invalid. Please revise the full extractNumeric logic to handle only the sign immediately before the number, treat any other digits in the string as ambiguous/invalid, and match all sample outputs exactly.

**Prompt 3 (May 3, 2026):**  
Update the code to correctly handle '--A2.5---', 'result: -2.E+3end', 'hello +.75world', '1e+', and '12.34.56'. Make sure main() matches the sample run exactly (including output formatting and "Program terminated."). Provide the complete compilable .cpp file.

**Which parts were AI-generated vs student-written:**
- AI-generated: The complete `parseNumber` function and `extractNumeric` logic (state machine, sign handling, decimal/exponent parsing, ambiguity check).
- Student-written: `main()` function and input loop, the `mant_digits > 15` rule for large integers, final testing, integration, and all documentation in this README.

**Modifications made:**
- Added the large integer rejection rule to match the sample run.
- Strengthened the check for other digits anywhere in the string.
- Performed extensive testing against every example in the lab description until all outputs matched exactly.

### Verification Statement
- I confirm that I understand every line of the code. I have reviewed the state machine in `parseNumber` and how it handles signs, mantissa, decimal point, and exponent.
- The code has been tested and works as intended on all sample inputs provided in the lab.
- I did not blindly copy-paste. I reviewed, modified, and re-tested the code until it was correct.
- One design choice: pure integers with more than 15 significant digits and no scientific notation are rejected (to match the sample expectation and stay within the spirit of the "range of a double" rule).

---

## Files in this repository
- `lab12.cpp` — Complete C++ solution
- `README.md` — This file (full GAI disclosure included)



---

*This lab was completed following University of Kansas academic integrity guidelines for Generative AI use. All AI assistance is fully disclosed above.*
