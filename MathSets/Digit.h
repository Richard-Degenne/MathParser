/**
 * \file	Digit.h
 * \brief	%Digit header file
 *
 * \see Digit
 *
 * \author Richard Degenne
 * \date 04-22-2014
 *
 */

#ifndef MathParser_Digit_h
#define MathParser_Digit_h

#include <iostream>
#include <stdexcept>

//#include "../templates/operators.h"


/**
 * Base-10 digits.
 * This is used as a basis for the Digit model, trying as much as possible not to use int.
 */
enum digit {
    ZERO =  0,
    ONE =   1,
    TWO =   2,
    THREE = 3,
    FOUR =  4,
    FIVE =  5,
    SIX =   6,
    SEVEN = 7,
    EIGHT = 8,
    NINE =  9
};


/**
 * Base-10 digit class.
 * %Digit class is used in every numeric classes and describes a base-10 digit behaviour
 */
class Digit {
private:
	/**
	 * %Digit value.
	 * `value` can be set through constructor or arithmetic operation.
	 * It is bound to be one of the #digit constants.
	 */
    digit value;

	/**
	 * %Digit overflow.
	 * Flag set when Digit::value overflows, when incremented from digit#NINE or decremented from digit#ZERO.
	 * The flag must be cleared manually by calling Digit::resetOverflow().
	 *
	 * \see Digit::resetOverflow()
	 * \see Digit::getOverflow()
	 */
    bool overflow;
    
    // Setters
    void incrementValue();
    void decrementValue();

    // Methods
    void printTo(std::ostream&) const;
    bool isEqualTo(Digit const&) const;
    bool isGreaterThan(Digit const&) const;
    
public:
    // Constructors
    Digit(); //!< Base constructor
    Digit(digit); //!< Specialized constructor
    Digit(Digit const&); //!< Copy constructor
    Digit(char const); //!< Parsing constructor
    
    // Getters
    bool getOverflow() const; //!< Getter for overflow
    
    // Setters
    void resetOverflow(); //!< Clears the object's Digit::overflow
    
    // Short operators overload
    Digit& operator= (Digit const&);
    Digit& operator+=(Digit const&);
    Digit& operator-=(Digit const&);
    Digit& operator*=(Digit const&);
    Digit& operator/=(Digit const&);
    Digit& operator%=(Digit const&);
	Digit& operator++(); //!< Pre-fixed increment
	Digit operator++(int); //!< Post-fixed increment
	Digit& operator--(); //!< Pre-fixed decrement
	Digit operator--(int); //!< Post-fixed decrement

	// Relational operators overload
	friend bool operator==(Digit const&, Digit const&);
	friend bool operator!=(Digit const&, Digit const&);
	friend bool operator> (Digit const&, Digit const&);
	friend bool operator>=(Digit const&, Digit const&);
	friend bool operator< (Digit const&, Digit const&);
	friend bool operator<=(Digit const&, Digit const&);

	// Stream operators overload
	friend std::ostream& operator<<(std::ostream&, Digit);
};

// Long operators overload
Digit operator+(Digit const&, Digit const&);
Digit operator-(Digit const&, Digit const&);
Digit operator*(Digit const&, Digit const&);
Digit operator/(Digit const&, Digit const&);
Digit operator%(Digit const&, Digit const&);

#endif /* defined(MathParser_Digit_h) */