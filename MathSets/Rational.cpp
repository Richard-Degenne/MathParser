/**
 * \file	Rational.cpp
 * \brief	%Rational source file
 * \details This file implements all of the Rational features.
 *
 * \author Richard Degenne
 * \date 04-22-2014
 *
 */

#include "Rational.h"

using namespace std;



/*
 * Constructors
 */

/**
 * \details	Instanciates a new Rational object with an empty Rational::numerator and a Digit#ONE Rational::denominator.
 */
Rational::Rational() : denominator{ONE, false} {

}

/**
 * \details	Instanciates a new Rational object with a single %Digit in its Rational::numerator.value and a digit#ONE in its Rational::denominator.value.
 *
 * \param	source	%Digit to initialize the object with.
 * \param   newSign Sign that will be applied to Rational::numerator::sign
 */
Rational::Rational(Digit const source, bool const newSign) : numerator{source, newSign}, denominator{ONE, false} {

}

/**
 * \param	source	%Rational object to initialize the instance with.
 */
Rational::Rational(Rational const& source) : numerator{source.numerator}, denominator{source.denominator} {

}

/**
 * \details	Instanciates a new Rational object by parsing a string.
 *
 * \param	source	%Digit to initialize the instance with.
 * \throws	std::range_error — Non-digit character
 */
Rational::Rational(string const& source) : numerator{source.substr(0,source.find('/'))}, denominator{source.substr(source.find('/')+1)} {
	trim();
}


/*
 * Setters
 */

void Rational::trim() {
	numerator.trim();
	denominator.trim();
	numerator.sign ^= denominator.sign; // See a truth table to understand this one
	denominator.sign = false;
	
	Integer copynum{numerator}, copyden{denominator}, temp{};
	while(copyden != Integer{"0"}) {
		temp = copyden;
		copyden = copynum % copyden;
		copynum = temp;
	}
	numerator /= copynum;
	denominator /= copynum;
}


/*
 * Methods
 */

void Rational::printTo(ostream& stream) const {
	stream << numerator << "/" << denominator;
}

bool Rational::isEqualTo(Rational const& a) const {
	return numerator == a.numerator && denominator == a.denominator;
}

bool Rational::isGreaterThan(Rational const& a) const {
	return numerator*a.denominator > a.numerator*denominator;
}


/*
 * Short operators overload
 */

Rational& Rational::operator+=(Rational const& a) {
	numerator = numerator*a.denominator + denominator*a.numerator;
	denominator *= a.denominator;
	trim();
	return *this;
}

Rational& Rational::operator-=(Rational const& a) {
	Rational copy{a};
	copy.numerator *= Integer{ONE,true};
	*this += copy;
	return *this;
}

Rational& Rational::operator*=(Rational const& a) {
	numerator *= a.numerator;
	denominator *= a.denominator;
	trim();
	return *this;
}

Rational& Rational::operator/=(Rational const& a) {
	numerator *= a.denominator;
	denominator *= a.numerator;
	trim();
	return *this;
}

Rational& Rational::operator%=(Rational const& a) {
	return *this;
}


/*
 * Long operators overload
 */

Rational operator+(Rational const& a, Rational const& b) {
	Rational copy {a};
	copy += b;
	return copy;
}

Rational operator-(Rational const& a, Rational const& b) {
	Rational copy {a};
	copy -= b;
	return copy;
}

Rational operator*(Rational const& a, Rational const& b) {
	Rational copy {a};
	copy *= b;
	return copy;
}

Rational operator/(Rational const& a, Rational const& b) {
	Rational copy {a};
	copy /= b;
	return copy;
}

Rational operator%(Rational const& a, Rational const& b) {
	Rational copy {a};
	copy %= b;
	return copy;
}


/*
 * Relational operator overload
 */

bool operator==(Rational const& a, Rational const& b) {
	return a.isEqualTo(b);
}

bool operator!=(Rational const& a, Rational const& b) {
	return !a.isEqualTo(b);
}

bool operator> (Rational const& a, Rational const& b) {
	return a.isGreaterThan(b);
}

bool operator>=(Rational const& a, Rational const& b) {
	return a.isGreaterThan(b) || a.isEqualTo(b);
}

bool operator< (Rational const& a, Rational const& b) {
	return !(a.isGreaterThan(b) || a.isEqualTo(b));
}

bool operator<=(Rational const& a, Rational const& b) {
	return !a.isGreaterThan(b);
}


/*
 * Stream operators overload
 */

ostream& operator<<(ostream& stream, Rational const& toPrint) {
	toPrint.printTo(stream);
	return stream;
}
