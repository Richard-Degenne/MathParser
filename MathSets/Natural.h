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
#include <stdexcept>
#include "Digit.h"

class Natural {
private:
    /*
     * A MathSets natural integer is basically a vector fo digits.
     * Index 0 will be for the highest power digit. (big-endian-like)
     */
    std::vector<Digit> numbers;

    // Setters
    Natural& trim();
	Natural& clearOverflows();
	Natural multiplySingleDigit(Digit const&, Digit const&);

    // Methods
    void printTo(std::ostream&) const;
    bool isEqualTo(Natural const&) const;
    bool isGreaterThan(Natural const&) const;

public:
    // Constructors
    Natural();
	Natural(Digit const);
    Natural(Natural const&);
    Natural(std::string const&);
    
    // Short operators overload
    Natural& operator+=(Natural const&);
    Natural& operator-=(Natural const&);
    Natural& operator*=(Natural const&);
    Natural& operator/=(Natural const&);
    Natural& operator%=(Natural const&);
	Natural& operator++(); // Pre-fixed increment (++x)
	Natural operator++(int); // Post-fixed increment (x++)
	Natural& operator--(); // Pre-fixed decrement (--x)
	Natural operator--(int); // Post-fixed decrement (x--)

	// Relational operators overload
	friend bool operator==(Natural const&, Natural const&);
	friend bool operator!=(Natural const&, Natural const&);
	friend bool operator> (Natural const&, Natural const&);
	friend bool operator>=(Natural const&, Natural const&);
	friend bool operator< (Natural const&, Natural const&);
	friend bool operator<=(Natural const&, Natural const&);

	// Stream operators overload
	friend std::ostream& operator<<(std::ostream&, Natural const&);
};

// Long operators overload
Natural operator+(Natural const&, Natural const&);
Natural operator-(Natural const&, Natural const&);
Natural operator*(Natural const&, Natural const&);
Natural operator/(Natural const&, Natural const&);
Natural operator%(Natural const&, Natural const&);

#endif
