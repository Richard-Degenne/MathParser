/*
 * Integer.cpp
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 04/22/14
 *
 * Implementation of the Integer class, which describes the MathSets integer class.
 */

#include "Integer.h"

using namespace std;

/*
 * Constructors
 */

// Base constructor
Integer::Integer() {
    numbers.push_back(ZERO);
}

// Copy constructor
Integer::Integer(Integer const& source) {
    int i;
    
    for(i=0 ; i<source.getSize() ; i++) {
        numbers.push_back(source.getNumber(i));
    }
}

// Most evolved constructor: String parsing
Integer::Integer(string const source) {
    int i;
    
    for (i=0 ; i<source.size() ; i++) {
        if (isdigit(source[i])) {
            Digit toPush;
            switch (source[i]) {
                case '0':
                    toPush = ZERO;
                    break;
                case '1':
                    toPush = ONE;
                    break;
                case '2':
                    toPush = TWO;
                    break;
                case '3':
                    toPush = THREE;
                    break;
                case '4':
                    toPush = FOUR;
                    break;
                case '5':
                    toPush = FIVE;
                    break;
                case '6':
                    toPush = SIX;
                    break;
                case '7':
                    toPush = SEVEN;
                    break;
                case '8':
                    toPush = EIGHT;
                    break;
                case '9':
                    toPush = NINE;
                    break;
                default:
                    break;
            }
            numbers.push_back(toPush);
        }
    }
}


/*
 * Getters
 */

int Integer::getSize() const {
    return (int) numbers.size();
}

vector<Digit>::const_iterator Integer::getBegin() const {
    return numbers.begin();
}

Digit Integer::getNumber(int position) const {
    return numbers[position];
}


/*
 * Setters
 */

Integer& Integer::normalize(const Integer& a) {
    if(getSize() < a.getSize()) {
        while (getSize() < a.getSize()) {
            numbers.insert(numbers.begin(), ZERO);
        }
    }
    return *this;
}

Integer& Integer::trim() {
    while(numbers[0].getValue() == ZERO) {
        numbers.erase(numbers.begin());
    }
    return *this;
}


/*
 * Methods
 */

void Integer::printTo(ostream& stream) const {
    int i;
    
    for (i=0 ; i<numbers.size() ; i++) {
        stream << numbers[i];
    }
}

bool Integer::isEqualTo(Integer const& a) const {
	if(getSize() == a.getSize())
	{
		for(int i=0 ; i<getSize() ; i++)
		{
			if(getNumber(i) != a.getNumber(i)) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Integer::isGreaterThan(Integer const& a) const {
	if(getSize() > a.getSize()) {
		return true;
	}
	else if(getSize() < a.getSize()) {
		return false;
	}
	else {
		for(int i=0; i<getSize(); i++) {
			if(getNumber(i) > a.getNumber(i)) {
				return true;
			}
			else if(getNumber(i) < a.getNumber(i)) {
				return false;
			}
		}
	}
	return false;
}


/*
 * Short operators overload
 */

Integer Integer::operator+=(Integer& a) {
    int i;
    bool overflow = false;

    // Normalizing both of the operands
    normalize(a);
    a.normalize(*this);

    // Foreach digit, starting from units
    for(i=getSize()-1 ; i>=0 ; i--) {
        numbers[i]+=a.numbers[i];
        if(overflow) {
            numbers[i]+=ONE;
        }
        overflow = numbers[i].getOverflow();
        numbers[i].resetOverflow(); // Reseting overflow to avoid disturbing further calculations
    }
    if (overflow) { // Highest-digit overflow implies expanding the integer
        numbers.insert(numbers.begin(), ONE);
    }

    // Trimming
    trim();
    a.trim();
    return *this;
}

Integer Integer::operator-=(Integer& a) {
	if(a>=*this) {
		Integer toReturn("0");
		*this = toReturn;
		return *this;
	}
	int i,j;

	// Normalizing both the operands
	normalize(a);
	a.normalize(*this);

    // Foreach digit, starting from units
    for(i=getSize()-1 ; i>=0 ; i--) {
        numbers[i]-=a.numbers[i];

		// Propagating overflow
		j = i;
        while(numbers[j].getOverflow()) {
			if(j > 0) {
				numbers[j-1]--;
				numbers[j].resetOverflow();
				j--;
			}
			else {
				numbers.erase(numbers.begin());
			}
        }
    }
	
    // Trimming
    trim();
    a.trim();
    return *this;
}

Integer Integer::operator*=(Integer const& a) { // NIY
    return *this;
}

Integer Integer::operator/=(Integer const& a) { // NIY
    return *this;
}

Integer Integer::operator%=(Integer const& a) { // NIY
    return *this;
}


/*
 * Long operators overload
 */

Integer operator+(Integer const& a, Integer& b) {
    Integer copy(a);
    copy += b;
    return copy;
}

Integer operator-(Integer const& a, Integer& b) {
    Integer copy(a);
    copy -= b;
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

ostream& operator<<(ostream& stream, Integer const& integer) {
    integer.printTo(stream);
    return stream;
}