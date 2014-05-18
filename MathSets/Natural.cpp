/*
 * Natural.cpp
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 04/22/14
 *
 * Implementation of the Natural class, which describes the MathSets natural integer class.
 */

#include "Natural.h"

using namespace std;

/*
 * Constructors
 */

// Base constructor
Natural::Natural() {
    numbers.push_back(ZERO);
}

// Digit constructor
Natural::Natural(Digit const source) {
	numbers.push_back(source);
}

// Copy constructor
Natural::Natural(Natural const& source) : numbers(source.numbers) {

}

// Most evolved constructor: String parsing
Natural::Natural(string const& source) {
    for (string::const_iterator i {source.begin()} ; i!=source.end() ; i++) {
        if (isdigit(*i)) {
            Digit toPush{};
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
 * Setters
 */

Natural& Natural::trim() {
	clearOverflows();
	while(*(numbers.begin()) == ZERO && numbers.size() > 1) {
        numbers.erase(numbers.begin());
    }
    return *this;
}

Natural& Natural::clearOverflows() {
	for(vector<Digit>::iterator i {numbers.begin()} ; i != numbers.end() ; i++) {
		i->resetOverflow();
	}
	return *this;
}

Natural Natural::multiplySingleDigit(Digit const& a, Digit const& b) {
	Natural less {a};
	Natural more {b};
	Natural result {"0"};

	if(b < a) {
		swap(more, less);
	}
	while(less-- != Natural {"0"}) {
		result += more;
	}
	return result;
}


/*
 * Methods
 */

void Natural::printTo(ostream& stream) const {
    for (vector<Digit>::const_iterator i {numbers.begin()} ; i!=numbers.end() ; i++) {
        stream << *i;
    }
}

bool Natural::isEqualTo(Natural const& a) const {
	if(numbers.size() == a.numbers.size())
	{
		for(vector<Digit>::const_iterator i {numbers.begin()}, j {a.numbers.begin()} ; i!=numbers.end() ; i++)
		{
			if(*i != *j) {
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Natural::isGreaterThan(Natural const& a) const {
	if(numbers.size() > a.numbers.size()) {
		return true;
	}
	else if(numbers.size() < a.numbers.size()) {
		return false;
	}
	else {
		for(int i{0}; i<numbers.size(); i++) {
			if(numbers[i] > a.numbers[i]) {
				return true;
			}
			else if(numbers[i] < a.numbers[i]) {
				return false;
			}
		}
	}
	return false;
}


/*
 * Short operators overload
 */

Natural& Natural::operator+=(Natural const& a) {
	if(a == Natural {"0"}) {
		return *this;
	}
	if(*this == Natural {"0"}) {
		*this = a;
		return *this;
	}
	if(this->numbers.size() < a.numbers.size()) {
		Natural copy {a};
		copy += *this;
		*this = copy;
		return *this;
	}

    // Foreach digit, starting from units
    vector<Digit>::reverse_iterator i {numbers.rbegin()};
	vector<Digit>::const_reverse_iterator j {a.numbers.rbegin()};
	vector<Digit>::reverse_iterator toOverflow {};
	while(j != a.numbers.rend()) {
		// Checking *this lenght overflow
		*i += *j;

		// Propagating overflow
		toOverflow = numbers.rbegin() + distance(numbers.rbegin(),i);
        while(toOverflow != numbers.rend() && toOverflow->getOverflow()) {
			if(toOverflow != numbers.rend()-1) {
				++(*(next(toOverflow)));
				toOverflow->resetOverflow();
				toOverflow++;
			}
			else {
				numbers.insert(numbers.begin(), ONE);
				toOverflow->resetOverflow();
			}
        }
		i++;
		j++;
    }

    // Trimming
    trim();
    return *this;
}

Natural& Natural::operator-=(Natural const& a) {
	if(a>=*this) {
		*this = Natural {"0"};
		return *this;
	}
	if (a == Natural {"0"}) {
		return *this;
	}

    // Foreach digit, starting from units
	vector<Digit>::reverse_iterator i {numbers.rbegin()};
	vector<Digit>::const_reverse_iterator j {a.numbers.rbegin()};
	vector<Digit>::reverse_iterator toOverflow {};
 	while(i != numbers.rend() && j != a.numbers.rend()) {
		*i-=*j;

		// Propagating overflow
		toOverflow = numbers.rbegin() + distance(numbers.rbegin(),i);
        while(toOverflow != numbers.rend() && toOverflow->getOverflow()) {
			if(toOverflow != numbers.rend()-1) {
				--(*(next(toOverflow)));
				toOverflow->resetOverflow();
				toOverflow++;
			}
			else {
				numbers.erase(numbers.begin());
			}
        }
		i++;
		j++;
    }
	
    // Trimming
    trim();
    return *this;
}

Natural& Natural::operator*=(Natural const& a) {
	if(*this == Natural {"0"} || a == Natural {"0"}) {
		*this = Natural {"0"};
		return *this;
	}
	if(*this == Natural {"1"}) {
		*this = a;
		return *this;
	}
	if(a == Natural {"1"}) {
		return *this;
	}

	Natural copy {a};
	Natural result {"0"};
    Natural toAdd {};

	// Naive algorithm
	for(vector<Digit>::reverse_iterator i {numbers.rbegin()} ; i!=numbers.rend() ; i++) { // For each *this digit
		for(vector<Digit>::const_reverse_iterator j {a.numbers.rbegin()}; j!=a.numbers.rend() ; j++) { // For each a digit
			toAdd = multiplySingleDigit(*i, *j);
			// Adding zeros
			for (int power {0} ; power < distance(numbers.rbegin(),i)+distance(a.numbers.rbegin(),j) ; power++) {
				toAdd.numbers.push_back(ZERO);
			}
			toAdd.trim();
			result += toAdd;
		}
	}
	*this = result;
	trim();
	return *this;
}

Natural& Natural::operator/=(Natural const& a) { // NIY
    return *this;
}

Natural& Natural::operator%=(Natural const& a) { // NIY
    return *this;
}

Natural& Natural::operator++() {
	*this += Natural {"1"};
	return *this;
}

Natural Natural::operator++(int dummy) {
	Natural copy {*this};
	++(*this);
	return copy;
}

Natural& Natural::operator--() {
	*this -= Natural {"1"};
	return *this;
}

Natural Natural::operator--(int dummy) {
	Natural copy(*this);
	--(*this);
	return copy;
}


/*
 * Long operators overload
 */

Natural operator+(Natural const& a, Natural const& b) {
    Natural copy {a};
    copy += b;
    return copy;
}

Natural operator-(Natural const& a, Natural const& b) {
    Natural copy {a};
    copy -= b;
    return copy;
}

Natural operator*(Natural const& a, Natural const& b) {
    Natural copy {a};
    copy *= b;
    return copy;
}


/*
 * Relational operator overload
 */

bool operator==(Natural const& a, Natural const& b) {
	return a.isEqualTo(b);
}

bool operator!=(Natural const& a, Natural const& b) {
	return !a.isEqualTo(b);
}

bool operator> (Natural const& a, Natural const& b) {
	return a.isGreaterThan(b);
}

bool operator>=(Natural const& a, Natural const& b) {
	return a.isGreaterThan(b) || a.isEqualTo(b);
}

bool operator< (Natural const& a, Natural const& b) {
	return !(a.isGreaterThan(b) || a.isEqualTo(b));
}

bool operator<=(Natural const& a, Natural const& b) {
	return !a.isGreaterThan(b);
}


/*
 * Stream operators overload
 */

ostream& operator<<(ostream& stream, Natural const& integer) {
    integer.printTo(stream);
    return stream;
}