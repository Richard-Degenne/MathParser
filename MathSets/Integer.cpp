/**
 * \file	Integer.cpp
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
 * \details	Instanciates a new Natural object with an empty Integer::value.
 */
Integer::Integer() : sign{false} {

}

/**
 * \details	Instanciates a new Integer object with a single %Digit in its Integer::numbers.
 *
 * \param	source	%Digit to initialize the object with.
 * \param   newSign Sign to initialisze the object with.
 */
Integer::Integer(Digit const source, bool const newSign) : sign{newSign}, value{source} {
}

/**
 * \param	source	%Integer object to initialize the instance with.
 */
Integer::Integer(Integer const& source) : value{source.value}, sign{source.sign} {

}

/**
 * \details	Instanciates a new Integer object by parsing a string.
 *  Negative numbers are declared by using the `-` character at the beginning of the string.
 *
 * \param	source	String to initialize the instance with.
 * \throws	std::range_error — Non-digit character
 *
 * \example Integer {"1234"}
 * \example Integer {"-1234"}
 */
Integer::Integer(string const& source) : sign{source[0]=='-'}, value{source[0]=='-' ? source.substr(1,source.npos) : source} {

}


/*
 * Setters
 */

void Integer::trim() {
	value.trim();
	if(value == Natural{"0"}) {
		sign = false; // Sign is set to false if value < 0, to avoid having "-0".
	}
}


/*
 * Methods
 */

void Integer::printTo(ostream& stream) const {
	if(sign) {
		stream << "-";
	}
	value.printTo(stream);
}

bool Integer::isEqualTo(Integer const& a) const {
	if (sign == a.sign) {
		return value.isEqualTo(a.value);
	}
	else {
		return false;
	}
}

bool Integer::isGreaterThan(Integer const& a) const {
	if (sign != a.sign) {
		return a.sign;
	}
	return sign ^ value.isGreaterThan(a.value);
}


/*
 * Short operators overload
 */

Integer& Integer::operator+=(Integer const& a) {
	if(sign == a.sign) { // If both operands are positive or negative
		value += a.value;
	}
	else {
		if(value >= a.value) { // *this has the greatest absolute value
			value -= a.value;
		}
		else { // If *this has the least absolute value
			Integer copy{a};
			copy.value -= value;
			*this = copy;
			sign = a.sign;
		}
	}
	trim();
	return *this;
}

Integer& Integer::operator-=(Integer const& a) {
	if(sign == a.sign) { // If both operands are positive or negative
		if(value >= a.value) {
			value -= a.value;
		}
		else {
			Integer copy{a};
			copy.value -= this->value;
			*this = copy;
			sign = !sign;
		}
	}
	else { // If operands have different signs
		value += a.value; // Sign remains unchanged
	}
	trim();
	return *this;
}

Integer& Integer::operator*=(Integer const& a) {
	value *= a.value;
	sign ^= a.sign;
	trim();
	return *this;
}

Integer& Integer::operator/=(Integer const& a) {
	value /= a.value;
	sign ^= a.sign;
	trim();
	return *this;
}
Integer& Integer::operator%=(Integer const& a) {
	if(a == Integer{"0"}) {
		throw "std::domain_error — Modulo by zero";
	}
	if(sign) {
		value = a.value - (value%a.value); // (-a)%b = b - (a%b)
		sign = false; // Modulo is positive
	}
	else {
		value %= a.value;
	}
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
	cout << "Computing (" << copy << " -= " << b << ")" << endl;
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
