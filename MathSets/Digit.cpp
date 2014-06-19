/**
 * \file	Digit.cpp
 * \brief	%Digit source file
 * \details This file implements all of the Digit features.
 *
 * \author Richard Degenne
 * \date 04-22-2014
 *
 */

#include "Digit.h"

using namespace std;


/*
 * Constructors
 */

/**
 * \details	Instanciates a new %Digit object with a `false` overflow.
 */
Digit::Digit() : overflow(false) {
    
}

/**
 * \details	Instanciates a new %Digit object with an initial value and a `false` overflow.
 *
 * \param	source	digit value to initialize the new object with.
 */
Digit::Digit(digit const source) : value(source) {

}

/**
 * \details Instanciates a new %Digit object from another one.
 *
 * \param	source	%Digit object to initialize the new objet with.
 */
Digit::Digit(Digit const& source) : value(source.value), overflow(source.overflow) {

}

/**
 * \details	Instanciates a new %Digit object from a numeric character
 *
 * \param	source	Character to parse
 * \throws	std::range_error — Non-digit character
 */
Digit::Digit(char const source) : overflow(false){
	switch (source) {
		case '0':
			value = ZERO;
			break;
		case '1':
			value = ONE;
			break;
		case '2':
			value = TWO;
			break;
		case '3':
			value = THREE;
			break;
		case '4':
			value = FOUR;
			break;
		case '5':
			value = FIVE;
			break;
		case '6':
			value = SIX;
			break;
		case '7':
			value = SEVEN;
			break;
		case '8':
			value = EIGHT;
			break;
		case '9':
			value = NINE;
			break;
			
		default:
			throw range_error("std::range_error — Non-digit character");
			break;
	}
}


/*
 * Getters
 */

bool Digit::getOverflow() const {
    return overflow;
}


/*
 * Setters
 */

void Digit::resetOverflow() {
	overflow = false;
}

void Digit::incrementValue() {
	switch (value)
	{
		case ZERO:
			value = ONE;
			break;
		case ONE:
			value = TWO;
			break;
		case TWO:
			value = THREE;
			break;
		case THREE:
			value = FOUR;
			break;
		case FOUR:
			value = FIVE;
			break;
		case FIVE:
			value = SIX;
			break;
		case SIX:
			value = SEVEN;
			break;
		case SEVEN:
			value = EIGHT;
			break;
		case EIGHT:
			value = NINE;
			break;
		case NINE:
			overflow = true;
			value = ZERO;
			break;
		default:
			break;
	}
}

void Digit::decrementValue() {
	switch (value)
	{
		case ZERO:
			overflow = true;
			value = NINE;
			break;
		case ONE:
			value = ZERO;
			break;
		case TWO:
			value = ONE;
			break;
		case THREE:
			value = TWO;
			break;
		case FOUR:
			value = THREE;
			break;
		case FIVE:
			value = FOUR;
			break;
		case SIX:
			value = FIVE;
			break;
		case SEVEN:
			value = SIX;
			break;
		case EIGHT:
			value = SEVEN;
			break;
		case NINE:
			value = EIGHT;
			break;
		default:
			break;
	}
}


/*
 * Methods
 */

void Digit::printTo(ostream& stream) const {
    stream << value;
}

bool Digit::isEqualTo(Digit const& a) const {
	return value == a.value;
}

bool Digit::isGreaterThan(Digit const& a) const {
	return value > a.value;
}


/*
 * Short operators overload
 */


Digit& Digit::operator=(Digit const& a) {
	value = a.value;
	overflow = a.overflow;
	return *this;
}

Digit& Digit::operator+=(Digit const& a) {
	for(int i {0} ; i<a.value ; i++) {
		incrementValue();
	}
	return *this;
}

Digit& Digit::operator-=(Digit const& a) {
	for(int i {0} ; i<a.value ; i++) {
		decrementValue();
	}
	return *this;
}

Digit& Digit::operator*=(Digit const& a) {
	Digit copy {*this};
	for (int i {0} ; i<a.value-1; i++) {
		*this += copy;
	}
    return *this;
}

/**
 * \throws	std::domain_error — Division by zero
 */
Digit& Digit::operator/=(Digit const& a) {
	if(a == ZERO) {
		throw domain_error("std::domain_error — Division by zero");
	}
	Digit result {ZERO};
	while(*this >= a) {
		*this -= a;
		result++;
	}
	*this = result;
	return *this;
}

/**
 * \throws	std::domain_error — Remainder by zero
 */
Digit& Digit::operator%=(Digit const& a) {
	if(a == ZERO) {
		throw domain_error("std::domain_error — Remainder by zero");
	}
	while(*this >= a) {
		*this -= a;
	}
    return *this;
}

Digit& Digit::operator++() {
	incrementValue();
	return *this;
}

Digit Digit::operator++(int dummy) {
	Digit copy {*this};
	++(*this);
	return copy;
}

Digit& Digit::operator--() {
	decrementValue();
	return *this;
}

Digit Digit::operator--(int dummy) {
	Digit copy {*this};
	--(*this);
	return copy;
}


/*
 * Long operators overload
 */

Digit operator+(Digit const& a, Digit const& b) {
	Digit copy {a};
	copy += b;
	return copy;
}

Digit operator-(Digit const& a, Digit const& b) {
	Digit copy {a};
	copy -= b;
	return copy;
}

Digit operator*(Digit const& a, Digit const& b) {
	Digit copy {a};
	copy *= b;
	return copy;
}

Digit operator/(Digit const& a, Digit const& b) {
	Digit copy {a};
	copy /= b;
	return copy;
}

Digit operator%(Digit const& a, Digit const& b) {
	Digit copy {a};
	copy %= b;
	return copy;
}


/*
 * Relational operator overload
 */

bool operator==(Digit const& a, Digit const& b) {
	return a.isEqualTo(b);
}

bool operator!=(Digit const& a, Digit const& b) {
	return !a.isEqualTo(b);
}

bool operator> (Digit const& a, Digit const& b) {
	return a.isGreaterThan(b);
}

bool operator>=(Digit const& a, Digit const& b) {
	return a.isGreaterThan(b) || a.isEqualTo(b);
}

bool operator< (Digit const& a, Digit const& b) {
	return !(a.isGreaterThan(b) || a.isEqualTo(b));
}

bool operator<=(Digit const& a, Digit const& b) {
	return !a.isGreaterThan(b);
}


/*
 * Stream operators overload
 */

ostream& operator<<(ostream& stream, Digit digit) {
    digit.printTo(stream);
    return stream;
}