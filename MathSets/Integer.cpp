/**
 * \file    Integer.cpp
 * \brief	%Integer source file
 * \details This file implements all of the Integer features.
 *
 * \author Richard Degenne
 * \date 04-22-2014
 *
 */

#include "Integer.h"

using namespace std;



/*
 * Constructors
 */

/**
 * \details	Instanciates a new Natural object with an empty Natural::numbers.
 */
Integer::Integer() : sign{false} {

}

/**
 * \details	Instanciates a new Integer object with a single %Digit in its Integer::numbers.
 *
 * \param	source	%Digit to initialize the object with.
 * \param   newSign Sign to initialisze the object with.
 */
Integer::Integer(Digit const source, bool const newSign) : sign{newSign} {
	numbers.push_back(source);
}

/**
 * \param	source	%Integer object to initialize the instance with.
 */
Integer::Integer(Integer const& source) : Natural{source}, sign{source.sign} {

}

/**
 * \details	Instanciates a new Integer object by parsing a string.
 *  Negative numbers are declared by using the `-` character at the beginning of the string.
 *
 * \param	source	%Digit to initialize the instance with.
 * \throws	std::range_error — Non-digit character
 *
 * \example Integer {"1234"}
 * \example Integer {"-1234"}
 */
Integer::Integer(string const& source) : Natural{source[0] == '-' ? source.substr(1,source.npos) : source} { // Don't send the `-` character if present to avoid expection

}


/*
 * Setters
 */

void Integer::trim() {
    Natural::trim();
    sign = *this != Natural{"0"}; // Sign is set to false if *this == 0, to avoid having "-0".
}


/*
 * Methods
 */

void Integer::printTo(ostream& stream) const {
    if(sign) {
        cout << "-";
    }
    Natural::printTo(cout);
}

bool Integer::isEqualTo(Integer const& a) const {
    if (sign == a.sign) {
        return Natural::isEqualTo(a);
    }
    else {
        return false;
    }
}

bool Integer::isGreaterThan(Integer const& a) const {
    if (sign != a.sign) {
        return a.sign;
    }
    return sign ^ Natural::isGreaterThan(a);
}


/*
 * Short operators overload
 */

Integer& Integer::operator+=(Integer const& a) {
    if(sign == a.sign) {
        Natural::operator+=(a);
    }
    else {
        if(*this >= a) {
            Natural::operator-=(a);
        }
        else {
            Integer copy {a};
            copy.Natural::operator-=(*this);
            *this = copy;
        }
        sign = *this >= a ? this->sign : a.sign;
    }
    return *this;
}

Integer& Integer::operator-=(Integer const& a) {
    if(sign == a.sign) {
        if(*this >= a) {
            Natural::operator-=(a);
        }
        else {
            Integer copy {a};
            copy.Natural::operator-=(*this);
            *this = copy;
        }
    }
    else {
        Natural::operator+=(a);
        sign = *this >= a ? this->sign : a.sign;
    }
    return *this;
}

Integer& Integer::operator*=(Integer const& a) {
    Natural::operator*=(a);
    sign ^= a.sign;
    return *this;
}

Integer& Integer::operator/=(Integer const& a) {
    Natural::operator/=(a);
    sign ^= a.sign;
    return *this;
}


/*
 * Long operators overload
 */

Integer operator+(Integer const& a, Integer const& b) {
    Integer copy {a};
    copy += b;
    return copy;
}

Integer operator-(Integer const& a, Integer const& b) {
    Integer copy {a};
    copy -= b;
    return copy;
}

Integer operator*(Integer const& a, Integer const& b) {
    Integer copy {a};
    copy *= b;
    return copy;
}

Integer operator/(Integer const& a, Integer const& b) {
    Integer copy {a};
    copy /= b;
    return copy;
}

Integer operator%(Integer const& a, Integer const& b) {
    Integer copy {a};
    copy %= b;
    return copy;
}


/*
 * Relational operator overload
 */

bool operator==(Integer const& a, Integer const& b) {
	return a.isEqualTo(b);
}

bool operator!=(Integer const& a, Integer const& b) {
	return !a.isEqualTo(b);
}

bool operator> (Integer const& a, Integer const& b) {
	return a.isGreaterThan(b);
}

bool operator>=(Integer const& a, Integer const& b) {
	return a.isGreaterThan(b) || a.isEqualTo(b);
}

bool operator< (Integer const& a, Integer const& b) {
	return !(a.isGreaterThan(b) || a.isEqualTo(b));
}

bool operator<=(Integer const& a, Integer const& b) {
	return !a.isGreaterThan(b);
}


/*
 * Stream operators overload
 */

ostream& operator<<(ostream& stream, Integer const& toPrint) {
    toPrint.printTo(stream);
    return stream;
}