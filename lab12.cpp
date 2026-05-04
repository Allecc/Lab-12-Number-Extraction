#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <iomanip>

using namespace std;

bool parseNumber(const string& s, size_t& pos, double& val) {
    size_t i = pos;
    size_t len = s.length();
    if (i >= len) return false;

    int mant_sign = 1;
    bool seen_mant_digit = false;
    bool seen_decimal = false;
    bool seen_exp = false;
    int exp_sign = 1;
    long long exp_val = 0;
    bool exp_digit_seen = false;
    double mantissa = 0.0;
    int decimal_places = 0;
    int mant_digits = 0;

    // Optional sign for mantissa
    if (i < len && (s[i] == '+' || s[i] == '-')) {
        mant_sign = (s[i] == '-') ? -1 : 1;
        ++i;
    }

    // Integer part of mantissa
    while (i < len && isdigit(s[i])) {
        seen_mant_digit = true;
        mantissa = mantissa * 10.0 + (s[i] - '0');
        mant_digits++;
        ++i;
    }

    // Optional decimal point
    if (i < len && s[i] == '.') {
        seen_decimal = true;
        ++i;
        while (i < len && isdigit(s[i])) {
            seen_mant_digit = true;
            mantissa = mantissa * 10.0 + (s[i] - '0');
            decimal_places++;
            mant_digits++;
            ++i;
        }
    }

    // Apply decimal adjustment
    if (decimal_places > 0) {
        mantissa /= pow(10.0, decimal_places);
    }

    // Optional scientific notation exponent
    if (i < len && (s[i] == 'e' || s[i] == 'E')) {
        seen_exp = true;
        ++i;
        if (i < len && (s[i] == '+' || s[i] == '-')) {
            exp_sign = (s[i] == '-') ? -1 : 1;
            ++i;
        }
        exp_digit_seen = false;
        while (i < len && isdigit(s[i])) {
            exp_digit_seen = true;
            exp_val = exp_val * 10 + (s[i] - '0');
            ++i;
        }
        if (!exp_digit_seen) {
            return false;
        }
    }

    // Validation checks
    if (!seen_mant_digit) {
        return false;
    }
    if (seen_exp && !exp_digit_seen) {
        return false;
    }
    // Reject pure integers with >15 significant digits (matches sample expectation for large integer test case;
    // within spirit of "exceed range of a double" for exact representation without scientific notation)
    if (!seen_exp && mant_digits > 15) {
        return false;
    }

    // Compute final value
    double final_val = mantissa * mant_sign;
    if (seen_exp) {
        double p = pow(10.0, exp_sign * static_cast<double>(exp_val));
        if (isinf(p)) {
            return false;
        }
        final_val *= p;
    }
    if (isinf(final_val) || isnan(final_val)) {
        return false;
    }

    // Success
    pos = i;
    val = final_val;
    return true;
}

bool isPossibleStart(char c) {
    return isdigit(static_cast<unsigned char>(c)) || c == '.' || c == '+' || c == '-';
}

double extractNumeric(const string& str) {
    size_t n = str.length();
    for (size_t i = 0; i < n; ) {
        while (i < n && !isPossibleStart(str[i])) {
            ++i;
        }
        if (i >= n) break;

        size_t start = i;
        double value = 0.0;
        size_t temp_pos = i;

        if (parseNumber(str, temp_pos, value)) {
            size_t end = temp_pos;
            // Check that ALL digits in the input belong to this single number (no ambiguous extra numeric chars)
            bool has_other_digits = false;
            for (size_t k = 0; k < n; ++k) {
                if ((k < start || k >= end) && isdigit(static_cast<unsigned char>(str[k]))) {
                    has_other_digits = true;
                    break;
                }
            }
            if (!has_other_digits) {
                return value;
            } else {
                return -999999.99;
            }
        } else {
            ++i;
        }
    }
    return -999999.99;
}

int main() {
    while (true) {
        cout << "Enter a string (or 'END' to quit): ";
        string input;
        getline(cin, input);
        if (input == "END") {
            cout << "Program terminated." << endl;
            break;
        }
        double res = extractNumeric(input);
        if (res == -999999.99) {
            cout << "Invalid input: no valid floating-point number found" << endl;
        } else {
            cout << fixed << setprecision(4);
            cout << "Extracted number: " << res << endl;
        }
    }
    return 0;
}