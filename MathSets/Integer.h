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
public:
    // Constructors
    Integer();
    Integer(Integer const&);
    Integer(std::string);
    
    // Getters
    int getSize() const;
    std::vector<Digit>::const_iterator getBegin() const;
    Digit getNumber(int) const;
    
    // Methods
    void printTo(std::ostream&) const;
    
    // Short operators overload
    Integer operator+=(Integer &);
    Integer operator-=(Integer const&); // NIY
    Integer operator*=(Integer const&); // NIY
    Integer operator/=(Integer const&); // NIY
    Integer operator%=(Integer const&); // NIY
};

// Long operators overload
Integer operator+(Integer const&, Integer &);

// Stream operators overload
std::ostream& operator<<(std::ostream&, Integer const&);

#endif
