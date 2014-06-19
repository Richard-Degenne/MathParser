/**
 * \file	main.cpp
 * \brief	Test file
 * \details	This file will be used for tests and debug session, but will have no interest for the project itself.
 *
 * \author	Richard Degenne
 * \date	04-21-2014
 * \copyright	CC by-nc-sa
 *
 */

#include <iostream>
#include "MathSets/Natural.h"
#include "MathSets/Digit.h"
#include "MathSets/Integer.h"

#include "Examples/examples.h"

using namespace std;

int main(int argc, const char* argv[])
{

	bool const CUSTOM_CODE = true; // Set this to `true` if you want to try your own code

	if(CUSTOM_CODE) {
		///// CUSTOM ZONE /////

		try {
			Digit a {TWO}, b {THREE};
			cout << a+b << endl;
			cout << a-b << endl;
			cout << a*b << endl;
			cout << a/b << endl;
			cout << a%b << endl;
		}
		catch (exception& e) {
			cerr << e.what() << endl;
		}

		///// END OF CUSTOM ZONE /////
	}

	else {
		demo1();
	}
	return EXIT_SUCCESS;
}