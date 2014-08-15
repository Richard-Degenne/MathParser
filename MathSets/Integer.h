/**
 * \file	Integer.h
 * \brief	%Integer header file
 *
 * \see Integer
 *
 * \author Richard Degenne
 * \date 05-27-2014
 *
 */

#ifndef MathParser_Integer_h
#define MathParser_Integer_h

#include <iostream>
#include <string>
#include "Natural.h"
#include "Digit.h"

//#include "../templates/operators.h"

/**
 * %Integer set.
 *
 */
class Integer {
	private:
		/**
		 * %Integer sign.
		 * `false` means the value is positive. `true` means it is negative.
		 * Understand it as "not signed" and "signed".
		 */
		bool sign;

		/**
		 * %Integer value.
		 * Absolute value of the %Integer object.
		 */
		Natural value;

		// Methods
		void printTo(std::ostream&) const;
		bool isEqualTo(Integer const&) const;
		bool isGreaterThan(Integer const&) const;

		// Setters
		void trim();

	public:
		// Constructors
		Integer(); //!< Default constructor
		Integer(Digit const, bool const); //!< %Digit constructor
		Integer(Integer const&); //!< Copy constructor
		Integer(std::string const&); //!< Parsing constructor
		// Short operators overload
		Integer& operator+=(Integer const&);
		Integer& operator-=(Integer const&);
		Integer& operator*=(Integer const&);
		Integer& operator/=(Integer const&);
		Integer& operator%=(Integer const&);
/*		Integer& operator++(); //!< Pre-fixed increment
		Integer operator++(int); //!< Post-fixed increment
		Integer& operator--(); //!< Pre-fixed decrement
		Integer operator--(int); //!< Post-fixed decrement
*/
		// Relational operators overload
		friend bool operator==(Integer const&, Integer const&);
		friend bool operator!=(Integer const&, Integer const&);
		friend bool operator> (Integer const&, Integer const&);
		friend bool operator>=(Integer const&, Integer const&);
		friend bool operator< (Integer const&, Integer const&);
		friend bool operator<=(Integer const&, Integer const&);


	// Stream operators overload
	friend std::ostream& operator<<(std::ostream&, Integer const&);
};

// Long operators overload
Integer operator+(Integer const&, Integer const&);
Integer operator-(Integer const&, Integer const&);
Integer operator*(Integer const&, Integer const&);
Integer operator/(Integer const&, Integer const&);
Integer operator%(Integer const&, Integer const&);

#endif /* defined(MathParser_Integer_h) */
