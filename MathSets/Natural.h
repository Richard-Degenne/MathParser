/**
 * \file	Natural.h
 * \brief	Natural header file
 *
 * \see Digit
 *
 * \author Richard Degenne
 * \date 04-21-2014
 *
 */

#ifndef MathParser_Natural_h
#define MathParser_Natural_h

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Digit.h"
//#include "../templates/operators.h"

/**
 * %Natural integer set.
 * Please note that 0 is included in this set.
 */
class Natural {
    friend class Integer;
	protected:
		/**
		 * Natural numbers Digit array.
		 * Index 0 will be for the highest power Digit. (big-endian-like)
		 */
		std::vector<Digit> numbers;

		// Setters
		Natural& trim();
		Natural& clearOverflows();
		Natural multiplySingleDigit(Digit const&, Digit const&);

		// Methods
		void printTo(std::ostream&) const;
		bool isEqualTo(Natural const&) const;
		bool isGreaterThan(Natural const&) const;

	public:
		// Constructors
		Natural(); //!< Default constructor
		Natural(Digit const); //!< %Digit constructor
		Natural(Natural const&); //!< Copy constructor
		Natural(std::string const&); //!< Parsing constructor

		// Short operators overload
		Natural& operator+=(Natural const&);
		Natural& operator-=(Natural const&);
		Natural& operator*=(Natural const&);
		Natural& operator/=(Natural const&);
		Natural& operator%=(Natural const&);
		Natural& operator++(); //!< Pre-fixed increment
		Natural operator++(int); //!< Post-fixed increment
		Natural& operator--(); //!< Pre-fixed decrement
		Natural operator--(int); //!< Post-fixed decrement

		// Relational operators overload
		friend bool operator==(Natural const&, Natural const&);
		friend bool operator!=(Natural const&, Natural const&);
		friend bool operator> (Natural const&, Natural const&);
		friend bool operator>=(Natural const&, Natural const&);
		friend bool operator< (Natural const&, Natural const&);
		friend bool operator<=(Natural const&, Natural const&);

		// Stream operators overload
		friend std::ostream& operator<<(std::ostream&, Natural const&);
};

// Long operators overload
Natural operator+(Natural const&, Natural const&);
Natural operator-(Natural const&, Natural const&);
Natural operator*(Natural const&, Natural const&);
Natural operator/(Natural const&, Natural const&);
Natural operator%(Natural const&, Natural const&);

#endif /* defined(MathParser_Natural_h) */
