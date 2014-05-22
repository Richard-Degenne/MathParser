/*
 * demo1.cpp
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 05/22/14
 *
 * First demonstration file showing Natural addition and multiplication.
 */

#include "examples.h"

using namespace std;

void demo1() {
	cout << "Here we are ! Here is a little demonstration of what Natural is capable of." << endl << endl << "As you can see, the unsigned long operation owerflows and gives some of a random result." << endl << endl << "But the Natural numbers handles this 15-digit multiplication smoothly. Give it a try! ;)" << endl;

	cout << endl << endl << "===== MULTIPLICATION =====" << endl << endl;

	cout << "\t=== With Natural ===" << endl;
	cout << "12345678901234 * 98765432109876 = " <<
        Natural{"12345678901234"} * Natural{"98765432109876"} << endl;

	cout << "\t=== With unsigned long int ===" << endl;
    cout << "12345678901234 * 98765432109876 = " <<
        (unsigned long){12345678901234} * 98765432109876 << endl << endl;

    cout << "Of course, we can do the same thing with additions. Look at this:" << endl << endl;

	cout << "===== ADDITION =====" << endl << endl;

	cout << "\t=== With Natural ===" << endl;
	cout << "18446744073709551615 + 1 = " <<
        Natural{"18446744073709551615"} + Natural{"1"} << endl;

	cout << "\t=== With unsigned long int ===" << endl;
    cout << "18446744073709551615 + 1 = " <<
        ((unsigned long){LONG_LONG_MAX}+1) * 2  << endl << endl;

    cout << "However, since the Natural class doesn't handle negative numbers, we can't see how it outclasses standard numeric types with subtractions." << endl << endl << "Wait for me to implement relative integers, and we'll talk about it at this time!" << endl;
}