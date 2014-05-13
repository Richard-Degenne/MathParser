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

// Digit constructor
Integer::Integer(Digit const source) {
	numbers.push_back(source);
}

// Copy constructor
Integer::Integer(Integer const& source) {
    for(vector<Digit>::const_iterator i = source.numbers.begin() ; i!=source.numbers.end() ; i++) {
        numbers.push_back(*i);
    }
}

// Most evolved constructor: String parsing
Integer::Integer(string const source) {
    for (string::const_iterator i=source.begin() ; i!=source.end() ; i++) {
        if (isdigit(*i)) {
            Digit toPush;
            switch (*i) {
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
	trim();
}


/*
 * Getters
 */

int Integer::getSize() const {
    return (int) numbers.size();
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
			numbers[0].resetOverflow();
        }
    }
    return *this;
}

Integer& Integer::trim() {
    while(numbers.begin()->getValue() == ZERO && getSize() > 1) {
        numbers.erase(numbers.begin());
    }
    return *this;
}

Integer Integer::multiplySingleDigit(Digit const& a, Digit const& b) {
	Integer less(a);
	Integer more(b);
	Integer result("0");

	if(b < a) {
		swap(more, less);
	}
	while(less-- != (Integer) "0") {
		result += more;
	}
	return result;
}


/*
 * Methods
 */

void Integer::printTo(ostream& stream) const {
    for (vector<Digit>::const_iterator i=numbers.begin() ; i!=numbers.end() ; i++) {
        stream << *i;
    }
}

bool Integer::isEqualTo(Integer const& a) const {
	if(getSize() == a.getSize())
	{
		for(vector<Digit>::const_iterator i=numbers.begin(), j=a.numbers.begin() ; i!=numbers.end() ; i++)
		{
			if(*i != *j) {
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

Integer& Integer::operator+=(Integer const& a) { // TODO Think about how this could look like with an iterator mecanism
	if (a == (Integer) "0") {
		return *this;
	}
	if (*this == (Integer) "0") {
		*this = a;
		return *this;
	}

	Integer copy(a);

    // Foreach digit, starting from units
    vector<Digit>::reverse_iterator i = numbers.rbegin() ;
	vector<Digit>::reverse_iterator j = copy.numbers.rbegin();

	while(i != numbers.rend() && j != copy.numbers.rend()) {
		*i += *j;

		// Propagating overflow
		vector<Digit>::reverse_iterator toOverflow = numbers.rbegin() + distance(numbers.rbegin(),i);
        while(toOverflow != numbers.rend() && toOverflow->getOverflow()) {
			if(toOverflow != numbers.rend()-1) {
				++(*(next(toOverflow)));
				toOverflow->resetOverflow();
				toOverflow++;
			}
			else {
				numbers.insert(numbers.begin(), ONE);
				numbers.begin()->resetOverflow();
				prev(toOverflow)->resetOverflow();
			}
        }
		i++;
		j++;
    }

    // Trimming
    trim();
    return *this;
}

Integer& Integer::operator-=(Integer const& a) {
	if(a>=*this) {
		*this = (Integer) "0";
		return *this;
	}
	if (a == (Integer) "0") {
		return *this;
	}
	int i,j;

	Integer copy(a);
	// Normalizing both the operands
	normalize(a);
	copy.normalize(*this);

    // Foreach digit, starting from units
    for(i=getSize()-1 ; i>=0 ; i--) {
        numbers[i]-=copy.numbers[i];

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
    return *this;
}

Integer& Integer::operator*=(Integer const& a) {
	if(*this == (Integer) "0" || a == (Integer) "0") {
		*this = (Integer) "0";
		return *this;
	}
	if(*this == (Integer) "1") {
		*this = a;
		return *this;
	}
	if(a == (Integer) "1") {
		return *this;
	}

	Integer copy(a);
	Integer result("0");
	Integer toAdd;

	// Normalizing
	normalize(a);
	copy.normalize(*this);

	// Naive algorithm
	for(int i=getSize()-1 ; i>=0 ; i--) { // For each *this digit
		for(int j=getSize()-1 ; j>=0 ; j--) { // For each a digit
			Integer toAdd("0");
			toAdd = multiplySingleDigit(numbers[i], copy.numbers[j]);
			for (int power=0; power < (getSize()-(i+1))+(copy.getSize()-(j+1)); power++) { // Adding zeros according to current digits power
				toAdd.numbers.push_back(ZERO);
				toAdd.getNumber(toAdd.getSize()-1).resetOverflow();
			}
			toAdd.trim();
			result += toAdd;
		}
	}
	*this = result;
	trim();
	return *this;
}

Integer& Integer::operator/=(Integer const& a) { // NIY
    return *this;
}

Integer& Integer::operator%=(Integer const& a) { // NIY
    return *this;
}

Integer& Integer::operator++() {
	Integer inc("1");
	*this += inc;
	return *this;
}

Integer Integer::operator++(int dummy) {
	Integer copy(*this);
	++(*this);
	return copy;
}

Integer& Integer::operator--() {
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

Integer operator+(Integer const& a, Integer const& b) {
    Integer copy(a);
    copy += b;
    return copy;
}

Integer operator-(Integer const& a, Integer const& b) {
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