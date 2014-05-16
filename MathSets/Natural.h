/*
 * Natural.h
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 04/21/14
 *
 * Header of the Natural class, which describes the MathSets natural integer class.
 */

#ifndef MathParser_Natural_h
#define MathParser_Natural_h

#include <iostream>
#include <vector>
#include "Digit.h"

class Natural {
private:
    /*
     * A MathSets natural integer is basically a vector fo digits.
     * Index 0 will be for the highest power digit. (big-endian-like)
     */
    std::vector<Digit> numbers;

    // Setters
    Natural& normalize(Natural const&);
    Natural& trim();
	Natural& clearOverflows();
	Natural multiplySingleDigit(Digit const&, Digit const&);

public:
    // Constructors
    Natural();
	Natural(Digit const);
    Natural(Natural const&);
    Natural(std::string);

    // Methods
    void printTo(std::ostream&) const;
    bool isEqualTo(Natural const&) const;
    bool isGreaterThan(Natural const&) const;
    
    // Short operators overload
    Natural& operator+=(Natural const&);
    Natural& operator-=(Natural const&);
    Natural& operator*=(Natural const&);
    Natural& operator/=(Natural const&); // NIY
    Natural& operator%=(Natural const&); // NIY
	Natural& operator++(); // Pre-fixed increment (++x)
	Natural operator++(int); // Post-fixed increment (x++)
	Natural& operator--(); // Pre-fixed decrement (--x)
	Natural operator--(int); // Post-fixed decrement (x--)
};

// Long operators overload
Natural operator+(Natural const&, Natural const&);
Natural operator-(Natural const&, Natural const&);
Natural operator*(Natural const&, Natural const&);

// Relational operators overload
bool operator==(Natural const&, Natural const&);
bool operator!=(Natural const&, Natural const&);
bool operator> (Natural const&, Natural const&);
bool operator>=(Natural const&, Natural const&);
bool operator< (Natural const&, Natural const&);
bool operator<=(Natural const&, Natural const&);

// Stream operators overload
std::ostream& operator<<(std::ostream&, Natural const&);

#endif
