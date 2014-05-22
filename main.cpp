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

#include "examples.h"

using namespace std;

int main(int argc, const char* argv[])
{
	bool const DEBUG_MODE = true;

	if(DEBUG_MODE) {
		///// DEBUG ZONE /////

		try {
			Natural a{"4345"}, b{"4346"};
			cout << a/b << " + " << a%b << endl;
		}
		catch (exception& e) {
			cerr << e.what() << endl;
		}

		///// END OF DEBUG ZONE /////
	}

	else {
		demo1();
	}
	return EXIT_SUCCESS;
}