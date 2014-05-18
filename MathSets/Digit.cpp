/*
 * Digit.cpp
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 04/22/14
 *
 * Implementation of the Digit class, which describes the MathSets digit class.
 */

#include "Digit.h"

using namespace std;


/*
 * Constructors
 */

// Base constructor
Digit::Digit() : overflow(false) {
    
}

// Initialization constructor
Digit::Digit(digit const source) : value(source) {

}

// Copy constructor
Digit::Digit(Digit const& source) : value(source.value), overflow(source.overflow) {

}

Digit::Digit(int const source) : overflow(false){
	switch (source) {
		case 0:
			value = ZERO;
			break;
		case 1:
			value = ONE;
			break;
		case 2:
			value = TWO;
			break;
		case 3:
			value = THREE;
			break;
		case 4:
			value = FOUR;
			break;
		case 5:
			value = FIVE;
			break;
		case 6:
			value = SIX;
			break;
		case 7:
			value = SEVEN;
			break;
		case 8:
			value = EIGHT;
			break;
		case 9:
			value = NINE;
			break;
			
		default:
			value = ERROR;
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

Digit Digit::operator=(Digit const& a) {
	value = a.value;
	overflow = a.overflow;
	return *this;
}

Digit Digit::operator+=(Digit const& a) {
	for(int i {0} ; i<a.value ; i++) {
		incrementValue();
	}
	return *this;
}

Digit Digit::operator-=(Digit const& a) {
	for(int i {0} ; i<a.value ; i++) {
		decrementValue();
	}
	return *this;
}

Digit Digit::operator*=(Digit const& a) {
	Digit copy {*this};
	for (int i {0} ; i<a.value-1; i++) {
		*this += copy;
	}
    return *this;
}

Digit Digit::operator/=(Digit const& a) { // NIY
    return *this;
}

Digit Digit::operator%=(Digit const& a) { // NIY
    return *this;
}

Digit Digit::operator++() {
	incrementValue();
	return *this;
}

Digit Digit::operator++(int dummy) {
	Digit copy {*this};
	++(*this);
	return copy;
}

Digit Digit::operator--() {
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