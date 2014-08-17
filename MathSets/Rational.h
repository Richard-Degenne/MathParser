/**
 * \file	Rational.h
 * \brief	%Rational header file
 *
 * \see Rational
 *
 * \author Richard Degenne
 * \date 05-30-2014
 *
 */

#ifndef MathParser_Rational_h
#define MathParser_Rational_h

#include <iostream>
#include <string>

#include "Integer.h"
#include "Digit.h"
//#include "../templates/operators.h"

class Rational {
	private:
		Integer numerator;
		Integer denominator;

		// Methods
		void printTo(std::ostream&) const;
		bool isEqualTo(Rational const&) const;
		bool isGreaterThan(Rational const&) const;

		// Setters
		void trim();

	public:
		// Constructors
		Rational(); //!< Default constructor
		Rational(Digit const, bool const); //!< %Digit constructor
		Rational(Rational const&); //!< Copy constructor
		Rational(std::string const&); //!< Parsing constructor
		// Short operators overload
		Rational& operator+=(Rational const&);
		Rational& operator-=(Rational const&);
		Rational& operator*=(Rational const&);
		Rational& operator/=(Rational const&);
		Rational& operator%=(Rational const&);
		/*Rational& operator++(); //!< Pre-fixed increment
		 Rational operator++(int); //!< Post-fixed increment
		 Rational& operator--(); //!< Pre-fixed decrement
		 Rational operator--(int); //!< Post-fixed decrement
		 */
		// Relational operators overload
		friend bool operator==(Rational const&, Rational const&);
		friend bool operator!=(Rational const&, Rational const&);
		friend bool operator> (Rational const&, Rational const&);
		friend bool operator>=(Rational const&, Rational const&);
		friend bool operator< (Rational const&, Rational const&);
		friend bool operator<=(Rational const&, Rational const&);


		// Stream operators overload
		friend std::ostream& operator<<(std::ostream&, Rational const&);

		// Others
		friend Rational floor(Rational);
};

// Long operators overload
Rational operator+(Rational const&, Rational const&);
Rational operator-(Rational const&, Rational const&);
Rational operator*(Rational const&, Rational const&);
Rational operator/(Rational const&, Rational const&);
Rational operator%(Rational const&, Rational const&);

#endif /* defined(MathParser__Rational_h) */
