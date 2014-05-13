/*
 * Integer.h
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 04/21/14
 *
 * Header of the Integer class, which describes the MathSets integer class.
 */

#ifndef MathParser_Integer_h
#define MathParser_Integer_h

#include <iostream>
#include <vector>
#include "Digit.h"

class Integer {
private:
    /*
     * A MathSets integer is basically a vector fo digits.
     * Index 0 will be for the highest power digit. (big-endian-like)
     */
    std::vector<Digit> numbers;

    // Setters
    Integer& normalize(Integer const&);
    Integer& trim();
	Integer multiplySingleDigit(Digit const&, Digit const&);

public:
    // Constructors
    Integer();
	Integer(Digit const);
    Integer(Integer const&);
    Integer(std::string);
    
    // Getters
    int getSize() const;
    Digit getNumber(int) const;

    // Methods
    void printTo(std::ostream&) const;
    bool isEqualTo(Integer const&) const;
    bool isGreaterThan(Integer const&) const;
    
    // Short operators overload
    Integer& operator+=(Integer const&);
    Integer& operator-=(Integer const&);
    Integer& operator*=(Integer const&);
    Integer& operator/=(Integer const&); // NIY
    Integer& operator%=(Integer const&); // NIY
	Integer& operator++(); // Pre-fixed increment (++x)
	Integer operator++(int); // Post-fixed increment (x++)
	Integer& operator--(); // Pre-fixed decrement (--x)
	Integer operator--(int); // Post-fixed decrement (x--)
};

// Long operators overload
Integer operator+(Integer const&, Integer const&);
Integer operator-(Integer const&, Integer const&);
Integer operator*(Integer const&, Integer const&);

// Relational operators overload
bool operator==(Integer const&, Integer const&);
bool operator!=(Integer const&, Integer const&);
bool operator> (Integer const&, Integer const&);
bool operator>=(Integer const&, Integer const&);
bool operator< (Integer const&, Integer const&);
bool operator<=(Integer const&, Integer const&);

// Stream operators overload
std::ostream& operator<<(std::ostream&, Integer const&);

#endif
