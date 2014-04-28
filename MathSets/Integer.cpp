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
    int i,j;

    // Normalizing both of the operands
    normalize(a);
    a.normalize(*this);

    // Foreach digit, starting from units
    for(i=getSize()-1 ; i>=0 ; i--) {
        numbers[i]+=a.numbers[i];

		// Propagating overflow
		j = i;
        while(numbers[j].getOverflow()) {
			if(j > 0) {
				numbers[j-1]++;
				numbers[j].resetOverflow();
				j--;
			}
			else {
				numbers.insert(numbers.begin(), ONE);
				numbers[0].resetOverflow();
				numbers[j+1].resetOverflow();
			}
        }
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

Integer Integer::operator*=(Integer const& a) {
	// TODO Make this damn faster (maybe with Karatsuba algorithm?)
    Integer copy(*this);
	Integer count(a);
	Integer ref("0");

	if(a > *this) { // Slight optimization: Be sure to use the lowest operand as counter
		*this = count;
		swap(copy, count);
	}

	while (--count != ref) {
		*this += copy;
	}
	return *this;
}

Integer Integer::operator/=(Integer const& a) { // NIY
    return *this;
}

Integer Integer::operator%=(Integer const& a) { // NIY
    return *this;
}

Integer Integer::operator++() {
	Integer inc("1");
	*this += inc;
	return *this;
}

Integer Integer::operator++(int dummy) {
	Integer copy(*this);
	++(*this);
	return copy;
}

Integer Integer::operator--() {
	Integer inc("1");
	*this -= inc;
	return *this;
}

Integer Integer::operator--(int dummy) {
	Integer copy(*this);
	--(*this);
	return copy;
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

Integer operator*(Integer const& a, Integer const& b) {
    Integer copy(a);
    copy *= b;
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