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
Digit::Digit() : overflow(ZERO) {
    
}

// Initialization constructor
Digit::Digit(digit const source) : value(source) {
    Digit();
}

// Copy constructor
Digit::Digit(Digit const& source) {
	value = source.getValue();
	overflow = source.getOverflow();
}

Digit::Digit(int const source) {
    Digit();
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

digit Digit::getValue() const {
    return value;
}

bool Digit::getOverflow() const {
    return overflow;
}


/*
 * Setters
 */

void Digit::setValue(digit newValue) {
    switch (newValue) {
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

void Digit::incrementValue() {
	switch (getValue())
	{
		case ZERO:
			setValue(ONE);
			break;
		case ONE:
			setValue(TWO);
			break;
		case TWO:
			setValue(THREE);
			break;
		case THREE:
			setValue(FOUR);
			break;
		case FOUR:
			setValue(FIVE);
			break;
		case FIVE:
			setValue(SIX);
			break;
		case SIX:
			setValue(SEVEN);
			break;
		case SEVEN:
			setValue(EIGHT);
			break;
		case EIGHT:
			setValue(NINE);
			break;
		case NINE:
			setOverflow();
			setValue(ZERO);
			break;
		default:
			break;
	}
}

void Digit::decrementValue() {
	switch (getValue())
	{
		case ZERO:
			setOverflow();
			setValue(NINE);
			break;
		case ONE:
			setValue(ZERO);
			break;
		case TWO:
			setValue(ONE);
			break;
		case THREE:
			setValue(TWO);
			break;
		case FOUR:
			setValue(THREE);
			break;
		case FIVE:
			setValue(FOUR);
			break;
		case SIX:
			setValue(FIVE);
			break;
		case SEVEN:
			setValue(SIX);
			break;
		case EIGHT:
			setValue(SEVEN);
			break;
		case NINE:
			setValue(EIGHT);
			break;
		default:
			break;
	}
}

void Digit::setOverflow() {
	overflow = true;
}

void Digit::resetOverflow() {
	overflow = false;
}


/*
 * Methods
 */

void Digit::printTo(ostream& stream) const {
    stream << value;
}

bool Digit::isEqualTo(Digit const& a) const {
	return getValue() == a.getValue();
}

bool Digit::isGreaterThan(Digit const& a) const {
	return getValue() > a.getValue();
}


/*
 * Short operators overload
 */

Digit Digit::operator=(Digit const& a) {
	setValue(a.getValue());
	return *this;
}

Digit Digit::operator+=(Digit const& a) {
	int i;
	
	for(i=0 ; i<a.getValue() ; i++)
	{
		incrementValue();
	}
	return *this;
}

Digit Digit::operator-=(Digit const& a) {
	int i;
	
    for(i=0 ; i<a.getValue() ; i++)
	{
		decrementValue();
	}
	return *this;
}

Digit Digit::operator*=(Digit const& a) {
	int i;
	Digit copy(*this);
	for (i=0 ; i<a.getValue()-1; i++)
	{
		cout << "Adding " << copy.getValue() << " to " << getValue() << endl;
		*this+=copy;
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
	Digit copy(*this);
	++(*this);
	return copy;
}

Digit Digit::operator--() {
	decrementValue();
	return *this;
}

Digit Digit::operator--(int dummy) {
	Digit copy(*this);
	--(*this);
	return copy;
}


/*
 * Long operators overload
 */

Digit operator+(Digit const& a, Digit const& b) {
	Digit copy(a);
	copy += b;
	return copy;
}

Digit operator-(Digit const& a, Digit const& b) {
	Digit copy(a);
	copy -= b;
	return copy;
}

Digit operator*(Digit const& a, Digit const& b) {
	Digit copy(a);
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