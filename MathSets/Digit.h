/*
 * Digit.h
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 04/22/14
 *
 * Header of the Digit class, which describes the MathSets digit class.
 */

#ifndef MathParser_Digit_h
#define MathParser_Digit_h

#include <iostream>


/*
 * digit enumerated type
 *
 * This is used as a basis for the digit model, trying as much as possible not to use int.
 */

enum digit {
    ERROR = -1,
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


/*
 * Digit class
 *
 * A digit is characterized by a digital value and a boolean overflow.
 * It overloads common operators to interact as easily as possible with the other classes.
 */

class Digit {
private:
    digit value;
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
    Digit();
    Digit(digit);
    Digit(Digit const&);
    Digit(int const);
    
    // Getters
    bool getOverflow() const;
    
    // Setters
    void resetOverflow();
    
    // Short operators overload
    Digit operator= (Digit const&);
    Digit operator+=(Digit const&);
    Digit operator-=(Digit const&);
    Digit operator*=(Digit const&);
    Digit operator/=(Digit const&); // NIY
    Digit operator%=(Digit const&); // NIY
	Digit operator++(); // Pre-fixed increment (++x)
	Digit operator++(int); // Post-fixed increment (x++)
	Digit operator--(); // Pre-fixed increment (++x)
	Digit operator--(int); // Post-fixed increment (x++)

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
Digit operator/(Digit const&, Digit const&); // NIY
Digit operator%(Digit const&, Digit const&); // NIY

#endif
