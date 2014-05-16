/*
 * main.cpp
 * MathParser
 *
 * CC by-nc-sa Richard Degenne
 * Created on 04/21/14
 * 
 * This file will be used for tests and debug session, but will have no interest for the project itself.
 */

#include <iostream>
#include <limits>
#include "Natural.h"
#include "Digit.h"

using namespace std;

int main(int argc, const char* argv[])
{
	/*
	 * Here we are ! Here is a little demonstration of what Natural is capable of.
	 *
	 * As you can see, the unsigned long operation owerflows and gives some of a random result.
	 * But the Natural numbers handles this 15-digit multiplication smoothly. Give it a try! ;)
	 */

	cout << endl << "===== MULTIPLICATION =====" << endl << endl;

	cout << "\t=== With Natural ===" << endl;
	cout << (Natural) "12345678901234" * (Natural) "98765432109876" << endl;

	cout << "\t=== With unsigned long int ===" << endl;
	cout  << (unsigned long)12345678901234 * 98765432109876 << endl << endl;

	/*
	 * Of course, we can do the same thing with additions. Look at this:
	 */

	cout << endl << "===== ADDITION =====" << endl << endl;

	cout << "\t=== With Natural ===" << endl;
	cout << (Natural) "18446744073709551615" + (Natural) "1" << endl;

	cout << "\t=== With unsigned long int ===" << endl;
	cout << (unsigned long)(LONG_LONG_MAX+1) * 2  << endl;

	/*
	 * However, since the Natural class doesn't handle negative numbers, we can't see how it outclasses standard numeric types with subtractions.
	 * Wait for me to implement relative integers, and we'll talk about it at this time!
	 */

	return EXIT_SUCCESS;
}